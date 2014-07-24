#!/usr/bin/env python
'''
simple plotting tool
Author: T.M.Perry UW
'''
import ROOT
from ROOT import TH1F,TFile,TCanvas,TLegend,TLine,TLatex
from ROOT import gStyle
import cmsPrelim
#import cmsPrelim as cpr

gStyle.SetOptStat('')
tex = ROOT.TLatex()
tex.SetTextAlign(13)
tex.SetNDC(True)
# for "legend"
xpos = 0.58
ypos = 0.64
big = 0.04
sml = 0.03


extraName = ""
draw_res = False
draw_res_v_nvtx = False
draw_res_v_rho = False

draw_res = True
#draw_res_v_nvtx = True
#draw_res_v_rho = True

res_line0 = True
varnames = [
 "genOsc_1000_3p0",
# "genOsc_1000_3p5",
# "genOsc_1000_4p0",
# "genOsc_1000_4p5",
# "genOsc_1000_5p0",
# "genOsc_1000_6p0",
# "genOsc_1000_7p0",
# "genOsc_1000_10p0",
# "genOsc_1000_15p0",
# "genOsc_1000_20p0",
 ]

c_hlt = ROOT.EColor.kRed 
c_rec = ROOT.EColor.kCyan+2
c_pre = ROOT.EColor.kBlack

canx = 800
cany = 900
c1 = TCanvas('c1','c1',canx,cany)
c2 = TCanvas('c2','c2',canx,cany)
c3 = TCanvas('c3','c3',canx,cany)
c2.SetLogz()
c3.SetLogz()
for varname in varnames:
 
 theFile = TFile("./roots/BDTout.root")
 #theFile = TFile("./roots/TMVAoutput_%s.root"%(varname))

###          ###
#  resolution  #
###          ### 
######################################################################
 if draw_res:
  c1.cd()
  res_preEB = theFile.Get("res_preEB")
  res_preEB.SetName("res_preEB")
  res_preEB.SetLineColor(1)
  res_preEB.SetLineWidth(3)
  res_EBmax = res_preEB.GetMaximum()
  res_EBmean = res_preEB.GetMean()
  res_EBrms = res_preEB.GetRMS()
  res_preEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  
  res_recoEB = theFile.Get("res_recoEB")
  res_recoEB.SetName("res_recoEB")
  res_recoEB.SetLineColor(c_rec)
  res_recoEB.SetLineWidth(3)
  res_recoEBmax = res_recoEB.GetMaximum()
  res_recoEBmean = res_recoEB.GetMean()
  res_recoEBrms = res_recoEB.GetRMS()
  
  res_hltEB = theFile.Get("res_hltEB")
  res_hltEB.SetName("res_hltEB")
  res_hltEB.SetLineColor(c_hlt)
  res_hltEB.SetLineWidth(2)
  res_hltEBmax = res_hltEB.GetMaximum()
  res_hltEBmean = res_hltEB.GetMean()
  res_hltEBrms = res_hltEB.GetRMS()
  
  #res_legEB=TLegend(0.11,0.6,0.4,0.89)
  #res_legEB.SetFillColor(0)
  #res_legEB.SetBorderSize(0)
  #res_legEB.AddEntry(res_preEB,"unscaled")
  #res_legEB.AddEntry(res_recoEB,"RECO BDT applied")
  #res_legEB.AddEntry(res_hltEB,"HLT BDT applied")
  
  #res_statEB=TLegend(0.6,0.6,0.89,0.89)
  #res_statEB.SetFillColor(0)
  #res_statEB.SetBorderSize(0)
  #res_statEB.AddEntry(res_preEB,"Mean: %0.2f  RMS: %0.2f"%(res_EBmean,res_EBrms))
  #res_statEB.AddEntry(res_recoEB,"Mean: %0.2f  RMS: %0.2f"%(res_recoEBmean,res_recoEBrms))
  #res_statEB.AddEntry(res_hltEB,"Mean: %0.2f  RMS: %0.2f"%(res_hltEBmean,res_hltEBrms))
  
  EBMax = 1350
  #EBMax = max(res_EBmax,res_recoEBmax,res_hltEBmax)
 
  res_lineEB0 = TLine(0.,0.,0.,1.05*EBMax)
  res_lineEB0.SetLineWidth(1)
  res_lineEB0.SetLineStyle(2)
 
  res_preEB.SetMaximum(1.1*EBMax)
  res_preEB.SetTitle("Barrel")
  res_preEB.Draw("hist")
  res_recoEB.Draw("hist,sames")
  res_hltEB.Draw("hist,sames")
  #res_legEB.Draw("sames")
  #res_statEB.Draw("sames")

  tex.SetTextSize(big)
  tex.DrawLatex(xpos,ypos+0.25,"#color[%s]{Unscaled}"%(c_pre))
  tex.DrawLatex(xpos,ypos+0.15,"#color[%s]{HLT Trained}"%(c_hlt))
  tex.DrawLatex(xpos,ypos+0.05,"#color[%s]{RECO Trained}"%(c_rec))
  tex.SetTextSize(sml)
  tex.DrawLatex(xpos,ypos+0.2,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_pre,res_EBmean,res_EBrms))
  tex.DrawLatex(xpos,ypos+0.1,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_hlt,res_recoEBmean,res_recoEBrms))
  tex.DrawLatex(xpos,ypos,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_rec,res_hltEBmean,res_hltEBrms))
  cmsPrelim.prelim_noLumi()
  if res_line0: res_lineEB0.Draw()
  
  c1.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_res_EB%s.png"%(varname,extraName))
  
  res_preEE = theFile.Get("res_preEE")
  res_preEE.SetName("res_preEE")
  res_preEE.SetLineColor(1)
  res_preEE.SetLineWidth(3)
  res_EEmax = res_preEE.GetMaximum()
  res_EEmean = res_preEE.GetMean()
  res_EErms = res_preEE.GetRMS()
  res_preEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  
  res_recoEE = theFile.Get("res_recoEE")
  res_recoEE.SetName("res_recoEE")
  res_recoEE.SetLineColor(c_rec)
  res_recoEE.SetLineWidth(3)
  res_recoEEmean = res_recoEE.GetMean()
  res_recoEErms = res_recoEE.GetRMS()
  res_recoEEmax = res_recoEE.GetMaximum()
  
  res_hltEE = theFile.Get("res_hltEE")
  res_hltEE.SetName("res_hltEE")
  res_hltEE.SetLineColor(c_hlt)
  res_hltEE.SetLineWidth(2)
  res_hltEEmean = res_hltEE.GetMean()
  res_hltEErms = res_hltEE.GetRMS()
  res_hltEEmax = res_hltEE.GetMaximum()
  
  #res_legEE=TLegend(0.11,0.6,0.4,0.89)
  #res_legEE.SetFillColor(0)
  #res_legEE.SetBorderSize(0)
  #res_legEE.AddEntry(res_preEE,"Unscaled")
  #res_legEE.AddEntry(res_recoEE,"RECO BDT applied")
  #res_legEE.AddEntry(res_hltEE,"HLT BDT applied")
  
  #res_statEE=TLegend(0.6,0.6,0.89,0.89)
  #res_statEE.SetFillColor(0)
  #res_statEE.SetBorderSize(0)
  #res_statEE.AddEntry(res_preEE,"Mean: %0.2f  RMS: %0.3f"%(res_EEmean,res_EErms))
  #res_statEE.AddEntry(res_recoEE,"Mean: %0.2f  RMS: %0.3f"%(res_recoEEmean,res_recoEErms))
  #res_statEE.AddEntry(res_hltEE,"Mean: %0.2f  RMS: %0.3f"%(res_hltEEmean,res_hltEErms))
  
  EEMax = 750
  #EEMax = max(res_EEmax,res_recoEEmax,res_hltEEmax)
 
  res_lineEE0 = TLine(0.,0.,0.,1.05*EEMax)
  res_lineEE0.SetLineWidth(1)
  res_lineEE0.SetLineStyle(2)
 
  res_preEE.SetMaximum(1.1*EEMax)
  res_preEE.SetTitle("Endcap")
  res_preEE.Draw("hist")
  res_recoEE.Draw("hist,sames")
  res_hltEE.Draw("hist,sames")
  #res_legEE.Draw("sames")
  #res_statEE.Draw("sames")
  tex.SetTextSize(big)
  tex.DrawLatex(xpos,ypos+0.25,"#color[%s]{Unscaled}"%(c_pre))
  tex.DrawLatex(xpos,ypos+0.15,"#color[%s]{HLT Trained}"%(c_hlt))
  tex.DrawLatex(xpos,ypos+0.05,"#color[%s]{RECO Trained}"%(c_rec))
  tex.SetTextSize(sml)
  tex.DrawLatex(xpos,ypos+0.2,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_pre,res_EEmean,res_EErms))
  tex.DrawLatex(xpos,ypos+0.1,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_hlt,res_recoEEmean,res_recoEErms))
  tex.DrawLatex(xpos,ypos,"#color[%s]{Mean: %0.2f RMS: %0.3f}"%(c_rec,res_hltEEmean,res_hltEErms))
  cmsPrelim.prelim_noLumi()
  if res_line0: res_lineEE0.Draw()
  
  c1.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_res_EE%s.png"%(varname,extraName))

###          ###
#  res v nvtx  #
###          ### 
######################################################################
 if draw_res_v_nvtx:
  c2.cd()
  rvmin = 1
  rvmax = 2e3

  res_v_nvtx_line = TLine(0.,1.,0.,4.)
  res_v_nvtx_line.SetLineWidth(1)
  res_v_nvtx_line.SetLineStyle(2)

  res_v_nvtx_preEB = theFile.Get("res_v_nvtx_preEB")
  res_v_nvtx_preEB.SetName("res_v_nvtx_preEB")
  res_v_nvtx_preEB.SetTitle("Barrel: Unscaled")
  res_v_nvtx_preEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_preEB.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_preEB.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_preEB.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_preEB%s.png"%(varname,extraName))
  
  res_v_nvtx_recoEB = theFile.Get("res_v_nvtx_recoEB")
  res_v_nvtx_recoEB.SetName("res_v_nvtx_recoEB")
  res_v_nvtx_recoEB.SetTitle("Barrel: RECO Trained")
  res_v_nvtx_recoEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_recoEB.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_recoEB.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_recoEB.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_recoEB%s.png"%(varname,extraName))

  res_v_nvtx_hltEB = theFile.Get("res_v_nvtx_hltEB")
  res_v_nvtx_hltEB.SetName("res_v_nvtx_hltEB")
  res_v_nvtx_hltEB.SetTitle("Barrel: HLT Trained")
  res_v_nvtx_hltEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_hltEB.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_hltEB.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_hltEB.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_hltEB%s.png"%(varname,extraName))

  res_v_nvtx_preEE = theFile.Get("res_v_nvtx_preEE")
  res_v_nvtx_preEE.SetName("res_v_nvtx_preEE")
  res_v_nvtx_preEE.SetTitle("Barrel: Unscaled")
  res_v_nvtx_preEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_preEE.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_preEE.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_preEE.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_preEE%s.png"%(varname,extraName))
  
  res_v_nvtx_recoEE = theFile.Get("res_v_nvtx_recoEE")
  res_v_nvtx_recoEE.SetName("res_v_nvtx_recoEE")
  res_v_nvtx_recoEE.SetTitle("Barrel: RECO Trained")
  res_v_nvtx_recoEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_recoEE.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_recoEE.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_recoEE.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_recoEE%s.png"%(varname,extraName))

  res_v_nvtx_hltEE = theFile.Get("res_v_nvtx_hltEE")
  res_v_nvtx_hltEE.SetName("res_v_nvtx_hltEE")
  res_v_nvtx_hltEE.SetTitle("Barrel: HLT Trained")
  res_v_nvtx_hltEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_nvtx_hltEE.GetYaxis().SetTitle("Nr. Primary Vertices")
  res_v_nvtx_hltEE.GetZaxis().SetRangeUser(rvmin,rvmax)
  res_v_nvtx_hltEE.Draw("colz")
  if res_line0: res_v_nvtx_line.Draw()

  c2.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVv_hltEE%s.png"%(varname,extraName))

###         ###
#  res v rho  #
###         ### 
######################################################################
 if draw_res_v_rho:
  c3.cd()
  rrmin = 1
  rrmax = 2e3

  res_v_rho_line = TLine(0.,0.,0.,2.)
  res_v_rho_line.SetLineWidth(1)
  res_v_rho_line.SetLineStyle(2)

  res_v_rho_preEB = theFile.Get("res_v_rho_preEB")
  res_v_rho_preEB.SetName("res_v_rho_preEB")
  res_v_rho_preEB.SetTitle("Barrel: Unscaled")
  res_v_rho_preEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_preEB.GetYaxis().SetTitle("Rho")
  res_v_rho_preEB.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_preEB.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_preEB%s.png"%(varname,extraName))
  
  res_v_rho_recoEB = theFile.Get("res_v_rho_recoEB")
  res_v_rho_recoEB.SetName("res_v_rho_recoEB")
  res_v_rho_recoEB.SetTitle("Barrel: RECO Trained")
  res_v_rho_recoEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_recoEB.GetYaxis().SetTitle("Rho")
  res_v_rho_recoEB.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_recoEB.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_recoEB%s.png"%(varname,extraName))

  res_v_rho_hltEB = theFile.Get("res_v_rho_hltEB")
  res_v_rho_hltEB.SetName("res_v_rho_hltEB")
  res_v_rho_hltEB.SetTitle("Barrel: HLT Trained")
  res_v_rho_hltEB.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_hltEB.GetYaxis().SetTitle("Rho")
  res_v_rho_hltEB.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_hltEB.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_hltEB%s.png"%(varname,extraName))

  res_v_rho_preEE = theFile.Get("res_v_rho_preEE")
  res_v_rho_preEE.SetName("res_v_rho_preEE")
  res_v_rho_preEE.SetTitle("Barrel: Unscaled")
  res_v_rho_preEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_preEE.GetYaxis().SetTitle("Rho")
  res_v_rho_preEE.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_preEE.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_preEE%s.png"%(varname,extraName))
  
  res_v_rho_recoEE = theFile.Get("res_v_rho_recoEE")
  res_v_rho_recoEE.SetName("res_v_rho_recoEE")
  res_v_rho_recoEE.SetTitle("Barrel: RECO Trained")
  res_v_rho_recoEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_recoEE.GetYaxis().SetTitle("Rho")
  res_v_rho_recoEE.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_recoEE.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_recoEE%s.png"%(varname,extraName))

  res_v_rho_hltEE = theFile.Get("res_v_rho_hltEE")
  res_v_rho_hltEE.SetName("res_v_rho_hltEE")
  res_v_rho_hltEE.SetTitle("Barrel: HLT Trained")
  res_v_rho_hltEE.GetXaxis().SetTitle("(genEnergy-(scRawEnergy+scPreshowerEnergy))/genEnergy")
  res_v_rho_hltEE.GetYaxis().SetTitle("Rho")
  res_v_rho_hltEE.GetZaxis().SetRangeUser(rrmin,rrmax)
  res_v_rho_hltEE.Draw("colz")
  if res_line0: res_v_rho_line.Draw()

  c3.Print("/afs/hep.wisc.edu/home/tperry/www/HLT/on_off_comp/7_1_2/BDT/%s_rVr_hltEE%s.png"%(varname,extraName))
