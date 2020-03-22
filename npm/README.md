# watch-mac
Watch for file (folder) changes [C++ For MAC]

High-performance C ++ file monitoring system



##### Usage:	watch-mac path

##### Result:	CreteFileEvent	path

​				MoveFileEvent	path
​				MoveFileEvent	fromPath	toPath
​				MoveFileInEvent	path
​				MoveFileOutEvent	path
​				DeleteFileEvent	path
​				ModifyFileEvent	path

Watch for file (folder) changes [C++ For MAC]
Copyright ©2020 ntfstool.com

#### For example:

watch-mac     . /Volumes

... you will capturing external disk mount events now...



```javascript
var watchmac = require('watch-mac');
var path = "/Volumes";

watchmac(path,function (data) {
    console.warn(data,"retData");
});
```