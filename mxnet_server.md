#. workdir 
```
cd  ~/Documents/face_recognize
```

#. stop mxnet 
```
mxnet-model-server --stop
```

#. delete .mar file in mar_file folder 
```
rm -R mar_file/*.mar
```

#. build mar file 
```
model-archiver --model-name getembed --model-path ./ --handler mx_api:handle --export-path ./
mv getembed.mar  mar_file/
```

#. run mxnet model 

mxnet-model-server --mms-config ../config.properties --model-store ./
```
cd mar_file/
mxnet-model-server --mms-config ~/Documents/face_recognize/config.properties --model-store ./
```

#. call model 
open a new terminal arbitrarily

```
curl -X POST "localhost:8081/models?url=getembed.mar&batch_size=1&max_batch_delay=10&initial_workers=1"
```

```
curl -X POST http://210.245.51.29:8003/predictions/getembed -T "17.png"
```
