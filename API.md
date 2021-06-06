## NetStream
这是一个能够把数据写入需要的网络流中的一组API借口，使用的是默认小端平台向大段网络字节序写数据。
### API接口
| API | 说明 | 示例 |
| -- | -- | -- |
| CNetStream|创建一个网络流| 
| GetWriteLen| 获取已经写入的字节数|
| GetReadLen| 获得已经读出的字节数|
| GetWriteLeftLen| 获取在len长度的字节流中还没有写入的字节数|
|GetReadLeftLen | 取在len长度的字节流中还没有读出的字节数|
|GetBaseAddr | 获取数据的基地址|
| Reset| （在修改模式下）充值当前定位的地址|
| Seek| 在修改模式下）进入修改模式，并且找到对应的index|
|ModefyNByte|（修改模式下）在某位置插入数据流|
|ModefyDWord|（修改模式下）写入DWORD|
|ModefyWord|（修改模式下）写入WORD|
|ModefyByte|（修改模式下）写入BYTE|
|WriteNByte|写入数据流|
|WriteDWord|写入DWORD|
|WriteWord|写入WORD|
|WriteByte|写入BYTE|
|ReadNByte|读出数据流|
|ReadDWord|读出DWORD|
|ReadWord|读出WORD|
|ReadByte|读出BYTE|

## ProtocolBuffer
这是一个把参数中msg的数据给按照要求的数据格式给写入对应的输出网络数据流中，其中的参数raw_flag都表示直接写入数据还是按照协议中（id + length + data）的形式写入数据
### API接口
| API | 说明 | 示例 |
| -- | -- | -- |
|PackStringData|打包字符串数据|
|PackByteData|打包BYTE数据|
|PackWordData|打包WORD数据|
|PackDWordData|打包DWORD数据|
|Pack|按照传入的msg中的ID类型来进行对应的打包|

## ProtocolPackingTool
这是打包和拆包工具类，在组装好所有的payload数据以后，通过这一组API来增加头部，或者是在获取应答的时候进行解析包头并把数据存入msg结构体
### API接口
| API | 说明 | 示例 |
| -- | -- | -- |
|PackSendData|打包数据增加头部|
|ParseReceiveData|解析数据，解析头部|
