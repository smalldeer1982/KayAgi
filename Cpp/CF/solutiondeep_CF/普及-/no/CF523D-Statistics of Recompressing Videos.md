# 题目信息

# Statistics of Recompressing Videos

## 题目描述

A social network for dogs called DH (DogHouse) has $ k $ special servers to recompress uploaded videos of cute cats. After each video is uploaded, it should be recompressed on one (any) of the servers, and only after that it can be saved in the social network.

We know that each server takes one second to recompress a one minute fragment. Thus, any server takes $ m $ seconds to recompress a $ m $ minute video.

We know the time when each of the $ n $ videos were uploaded to the network (in seconds starting from the moment all servers started working). All videos appear at different moments of time and they are recompressed in the order they appear. If some video appeared at time $ s $ , then its recompressing can start at that very moment, immediately. Some videos can await recompressing when all the servers are busy. In this case, as soon as a server is available, it immediately starts recompressing another video. The videos that await recompressing go in a queue. If by the moment the videos started being recompressed some servers are available, then any of them starts recompressing the video.

For each video find the moment it stops being recompressed.

## 样例 #1

### 输入

```
3 2
1 5
2 5
3 5
```

### 输出

```
6
7
11
```

## 样例 #2

### 输入

```
6 1
1 1000000000
2 1000000000
3 1000000000
4 1000000000
5 1000000000
6 3
```

### 输出

```
1000000001
2000000001
3000000001
4000000001
5000000001
5000000004
```

# AI分析结果

### 题目翻译
# 视频重新压缩统计

## 题目描述
一个名为 DH（DogHouse）的狗狗社交网络有 $k$ 个特殊服务器，用于重新压缩上传的可爱猫咪视频。每个视频上传后，都应在其中一台（任意一台）服务器上进行重新压缩，只有这样才能保存在社交网络中。

我们知道，每台服务器重新压缩一分钟的视频片段需要一秒钟。因此，任何一台服务器重新压缩一个 $m$ 分钟的视频需要 $m$ 秒钟。

我们知道 $n$ 个视频中每个视频上传到网络的时间（从所有服务器开始工作的时刻起，以秒为单位）。所有视频的上传时间都不同，并且它们将按照出现的顺序进行重新压缩。如果某个视频在时间 $s$ 出现，那么它的重新压缩可以立即在该时刻开始。当所有服务器都处于忙碌状态时，一些视频可能需要等待重新压缩。在这种情况下，一旦有服务器可用，它将立即开始重新压缩另一个视频。等待重新压缩的视频将排成一个队列。如果在视频开始重新压缩的时刻有服务器可用，那么其中任何一台服务器都可以开始重新压缩该视频。

对于每个视频，找出它结束重新压缩的时刻。

## 样例 #1

### 输入
```
3 2
1 5
2 5
3 5
```

### 输出
```
6
7
11
```

## 样例 #2

### 输入
```
6 1
1 1000000000
2 1000000000
3 1000000000
4 1000000000
5 1000000000
6 3
```

### 输出
```
1000000001
2000000001
3000000001
4000000001
5000000001
5000000004
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟视频压缩的过程，利用优先队列来维护服务器的空闲时间，以高效地处理每个视频的压缩任务。具体思路是根据服务器的使用情况分为两种情况：若有空闲服务器，视频直接开始压缩，结束时间为上传时间加上压缩时长；若没有空闲服务器，则等待最早结束压缩的服务器，视频在该服务器结束上一个任务后开始压缩。

各题解的算法要点在于使用小根堆（优先队列）来存储服务器的空闲时间，确保能快速找到最早空闲的服务器。解决的难点在于正确处理视频的上传时间和服务器的空闲时间，以确定每个视频的开始和结束压缩时间。

### 评分较高的题解
- 作者：我和鱼过不去 (4星)
    - 关键亮点：思路清晰，对优先队列的使用和两种情况的处理解释详细，代码简洁易懂。
- 作者：流绪 (4星)
    - 关键亮点：贪心模拟思路明确，对小根堆的作用解释清晰，代码有详细注释。
- 作者：Zeryboy (4星)
    - 关键亮点：题目分析和解题思路步骤详细，代码规范，对优先队列的初始化和使用有清晰的说明。

### 重点代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
priority_queue<long long,vector<long long>,greater<long long> >q; 
int main()
{
      scanf("%d%d",&n,&k);
      for(int i=1;i<=n;i++)
      {
            long long s,m;
            scanf("%lld%lld",&s,&m);
            if(q.size()>=k)  //情况2 
            {
                  s = max(s,q.top()) + m;  
                  q.pop();
            }
            else s += m;   //情况1 
            q.push(s);    //将当前视频结束压缩的时间加入队列 
            printf("%lld\n",s);  //输出结束压缩的时间 
      }
      return 0;
} 
```
**核心实现思想**：使用优先队列 `q` 来存储服务器的空闲时间（即视频结束压缩的时间）。对于每个视频，根据队列的大小判断服务器是否空闲，若空闲则直接计算结束时间，若不空闲则等待最早空闲的服务器，更新结束时间并将其加入队列，最后输出结束时间。

### 关键思路或技巧
- 使用优先队列（小根堆）来维护服务器的空闲时间，能在 $O(log k)$ 的时间复杂度内找到最早空闲的服务器。
- 注意数据范围，使用 `long long` 类型避免溢出。

### 拓展思路
同类型题或类似算法套路：任务调度问题，如多线程任务分配、CPU 任务调度等，都可以使用优先队列来模拟任务的执行过程，根据任务的优先级（如结束时间、执行时长等）进行调度。

### 洛谷题目推荐
- P1803 凌乱的yyy / 线段覆盖
- P2123 皇后游戏
- P1080 国王游戏

### 个人心得摘录与总结
- 作者：Silence_World：提到此题数据非常大，使用 `cin` 和 `cout` 无法通过，需要使用 `scanf` 和 `printf` 进行输入输出，提醒在处理大数据时要注意输入输出的效率。
- 作者：xiaojuruo：提到“十年OI一场空，不开longlong见祖宗”，强调在处理可能出现大数值的题目时，要注意数据类型的选择，避免因数据溢出导致错误。 

---
处理用时：35.34秒