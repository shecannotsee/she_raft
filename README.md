

### 服务器状态

一个服务器会有三种状态中的一种

1. Follow-追随者状态
2. Candidate-候选状态
3. Leader-领导者状态

注：Raft 通过比较两份日志中最后一条日志条目的索引值和任期号来定义谁的日志比较新

#### 初始状态

初始态为follow

### 对于follow状态

**投票动作**：1.在选举时间内收到求票通知 2.自己还没投票 

-> 动作：

1.给求票者投票 2.自己的选票变为零 3.重置选举轮询时间



**拒绝投票动作**：当candidate的日志信息比当前的follow还要老旧，follow会拒绝投票

**触发状态改变条件**：

1.没有收到leader的消息 2.选举超时 

-> 动作：

1.增加自己的term 2.自身变为candidate状态  3.向其他节点（是其他所有节点吗？是的）请求投票，其他节点

**保持follow状态**：

收到leader的心跳消息 

-> 动作：

1.向leader发送心跳消息 2.重置选举轮询时间

**tips**:

有一个控制选举的超时设置：选举超时随机在150-300毫秒之间
有一个用来标识的版本的term



### 对于candidate状态

**触发状态改变条件**：

获得大多数节点的投票 

-> 动作：

自身变为leader



**触发状态改变条件**：

产生了新的leader 

-> 动作：

自身变为follow

动作2：没有获得大多数节点的投票 或者 选举时间超时 

-> 动作：

重置自身的选举时间，term增加一个单位



对于其他leader发来的消息：通过版本号term来决定动作 -> 版本号大于当前candidate版本号term（candidate回退为follow），小于等于（不予理会）

有一个控制选举时间的超时设置：



#### 对于leader状态（每届唯一）：

触发状态改变条件：
保持leader的动作：向follow发送心跳消息，用来确认leader的地位

心跳发送设置：发送心跳消息的间隔时间






统一动作：通过心跳消息传递日志信息，心跳消息可以附加额外的消息例如日志信息

### 日志复制

对于一个更改动作：

1. 向leader发出更改请求request
2. leader暂存该请求
3. leader向所有follow发出该请求request
4. follow对request进行暂存，暂存后将暂存消息返回给leader
5. 若大多数follow均已暂存该request，则leader将该request进行提交submit
6. leader提交后向所有follow发出提交请求submit
7. 是否在收到大多数follow的submit之后才告知client已经完成动作？是的
8. follow在下一次收到leader的心跳的时候会去做这个submit【安全性的保障之一】

- 注1：leader在特定的任期号内的一个日志索引处最多创建一个日志条目
- 注2：在follow接受request时，会进行一致性检查，如果不一致，还需要进行同步操作（leader通过nextindex来对follow的日志进行定位，定位成功后进行同步，leader同步到follow）



### 安全性

安全性：对落后的follow，在leader崩溃后被选举成leader之后，可能造成问题，需要进行进一步处理
1.当前term不会提交之前的term的日志条目（？5.4.2的疑问？），用来保护leader提交后崩溃的情况



**缺陷1**：集群成员变更时可能划分成两个独立区域空间

**解决方法**：将集群切换到一个过渡配置（类似于缓冲区，有老设备+新设备）,集群一旦在过度配置进行一旦提交，那么将集群切到新设备中（然后更新老设备），然后再把更新的到新设备的单位加入到集群

注：新服务器在刚加入时没有选举权，过半的时候无需考虑到该服务器（因为没有日志，同步需要花费大量时间）。等新服务器日志追上来之后才会加入选举（有选举权）



**缺陷2**：那些被移除的服务器可能会扰乱集群，导致系统可用性差

**解决方法**：6 集群成员变更问题3



### 一些拓展技术：

1. 日志-快照技术：对指定数据集合的一个完全可用的拷贝，然后清空日志
2. 太落后的follow会舍弃日志，通过快照取代
3. 当日志大小 达到一个固定大小的时候就创建一次快照。如果这个阈值设置得显著大于期望的快照的大小， 那么快照的磁盘带宽负载就会很小
4. 是写入快照需要花费一段时间，可以通过写时复制的技术来，这样新的更新就可以在不影响正在写的快照的情况下被接收。

#### 拜占庭和非拜占庭错误

一般地，把出现故障( crash 或 fail-stop，即不响应)但不会伪造信息的情况称为“非拜占庭错误”( non-byzantine fault)或“故障错误”( Crash Fault);

伪造信息恶意响应的情况称为“拜占庭错误”( Byzantine Fault)，对应节点为拜占庭节点。



### 状态

#### 所有服务器上的持久状态：（在响应RPC之前更新了稳定存储）

**currentTerm**:已看到最新的术语服务器（已初始化为0）第一次开机时，频率单调增加）
**votedFor**:在当前选举中获得选票的候选人身份术语（如果没有，则为空）
**log[]**:日志条目；每个条目都包含状态机的命令，以及领导者接收条目时的术语（第一个索引为1）



#### 所有服务器上的不稳定状态：

**commitIndex**:已知要提交的最高日志项的索引（初始化为0，单调递增）
**lastApplied**:应用于状态机的最高日志项的索引（初始化为0，单调增加）



#### Volatile state on leaders:（选举后重新启动）

**nextIndex[]**:对于每个服务器，要发送到该服务器的下一个日志项的索引（初始化为leader last log index+1）
**matchIndex[]**:对于每台服务器，已知要在服务器上复制的最高日志项的索引（初始化为0，单调递增）



### RequestVote RPC【请求投票rpc】

#### 请求参数

**term**：候选人任期号（版本号）
**candidateId**：申请投票的候选人
**lastLogIndex**：候选人最后一个日志条目的索引
**lastLogTerm**：候选人最后一条日志对应的任期号（版本号）



#### 返回结果

**term**：当前任期，供候选人自我更新
**voteGranted：true**意味着候选人获得了选票



### AppendEntries RPC【附加条目RPC】

#### Arguments【参数，rpc的请求参数】

**term：leader**在任期期间的版本号
**leaderId**：
**prevLogIndex**：紧跟在新日志项之前的日志项索引
**prevLogTerm**：上一条日志的所对应的leader的任期号（版本号）
**entries[]**：要存储的日志条目（做心跳使用时为空；可能会发送多个以提高效率）
**leaderCommit**：leader's commitIndex



#### Results【rpc的请求结果】

**term**：currentTerm，用于leader自我更新
**success**：如果follower包含与prevLogIndex和prevLogTerm匹配的条目，则为true



### Rules for Servers【服务器规则】

#### 所有服务器：

- 如果CommitteIndex>lastApplied:increment lastApplied，则将日志[lastApplied]应用于状态机
- 如果RPC请求或响应包含术语T>currentTerm:set currentTerm=T，则转换为follower（§5.1）

#### follower：

- 回应candidates和leader的RPC
- 如果选举超时，没有收到当前leader的通知，也没有给candidates：投票，那么转为candidates：



#### candidates：

- 转换为候选人后，开始选举：

  1.增加当前的任期号（版本号）

  2.给自己投票

  3.重置选举计时器

  4.将RequestVote RPC发送到所有其他服务器

- 如果收到大多数服务器的投票，那么当前candidates成为leader

- 如果从新的leader那里收到AppendEntries RPC，那么他转变为follower

- 如果选举超时：开始新的选举



#### leader：

- 当选后：向每台服务器发送初始的空AppendEntries RPC（用作心跳）；在空闲期间重复此操作，以防止选举超时

- 如果从客户端收到命令：将条目附加到本地日志，则在条目应用到状态机后响应

- 如果最后一个日志索引≥follower的nextIndex，那么发送从nextIndex开始的带有日志项的AppendEntries RPC：

  1.如果成功：更新跟随者的nextIndex和matchIndex

  2.如果由于日志不一致导致AppendEntries失败：减少nextIndex并重试

- 如果存在一个N，使得N>commitIndex，则大多数匹配索引[i]≥ N、 和log[N]。term ==currentTerm，设置commitIndex=N



### 附加

#### 1.选举安全：

在给定的任期内，最多可以选出一名领导人



#### 2.Leader Append Only：

Leader从不覆盖或删除其日志中的条目；它只附加新条目
日志匹配：如果两个日志包含具有相同索引和术语的条目，那么在给定索引的所有条目中，日志都是相同的。



#### 3.leader完整性：

如果日志条目在给定期限内提交，那么该条目将出现在所有较高编号期限的leader日志中
状态机安全：如果服务器已将给定索引处的日志条目应用到其状态机，则没有其他服务器会为同一索引应用不同的日志条目
