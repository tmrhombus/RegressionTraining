RegressionTraining
==================
To run the configuration and make the training

```
./regression.exe run/ELE_710pre5.config 
```

To apply the training and make some histograms
```
root -l run/loadGBR.C run/BDTreader.C++
  BDTreader b;
  b.Loop()
  ```

To plot the histograms
```
python run/plotter.py
```
