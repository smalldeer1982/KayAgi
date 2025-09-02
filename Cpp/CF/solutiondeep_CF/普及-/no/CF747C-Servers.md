# 题目信息

# Servers

## 题目描述

There are $ n $ servers in a laboratory, each of them can perform tasks. Each server has a unique id — integer from $ 1 $ to $ n $ .

It is known that during the day $ q $ tasks will come, the $ i $ -th of them is characterized with three integers: $ t_{i} $ — the moment in seconds in which the task will come, $ k_{i} $ — the number of servers needed to perform it, and $ d_{i} $ — the time needed to perform this task in seconds. All $ t_{i} $ are distinct.

To perform the $ i $ -th task you need $ k_{i} $ servers which are unoccupied in the second $ t_{i} $ . After the servers begin to perform the task, each of them will be busy over the next $ d_{i} $ seconds. Thus, they will be busy in seconds $ t_{i},t_{i}+1,...,t_{i}+d_{i}-1 $ . For performing the task, $ k_{i} $ servers with the smallest ids will be chosen from all the unoccupied servers. If in the second $ t_{i} $ there are not enough unoccupied servers, the task is ignored.

Write the program that determines which tasks will be performed and which will be ignored.

## 说明/提示

In the first example in the second $ 1 $ the first task will come, it will be performed on the servers with ids $ 1 $ , $ 2 $ and $ 3 $ (the sum of the ids equals $ 6 $ ) during two seconds. In the second $ 2 $ the second task will come, it will be ignored, because only the server $ 4 $ will be unoccupied at that second. In the second $ 3 $ the third task will come. By this time, servers with the ids $ 1 $ , $ 2 $ and $ 3 $ will be unoccupied again, so the third task will be done on all the servers with the ids $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ (the sum of the ids is $ 10 $ ).

In the second example in the second $ 3 $ the first task will come, it will be performed on the servers with ids $ 1 $ and $ 2 $ (the sum of the ids is $ 3 $ ) during three seconds. In the second $ 5 $ the second task will come, it will be performed on the server $ 3 $ , because the first two servers will be busy performing the first task.

## 样例 #1

### 输入

```
4 3
1 3 2
2 2 1
3 4 3
```

### 输出

```
6
-1
10
```

## 样例 #2

### 输入

```
3 2
3 2 3
5 1 2
```

### 输出

```
3
3
```

## 样例 #3

### 输入

```
8 6
1 3 20
4 2 1
6 5 5
10 1 1
15 3 6
21 8 8
```

### 输出

```
6
9
30
-1
15
36
```

# AI分析结果

### 题目翻译
#### 服务器

#### 题目描述
实验室中有 $n$ 台服务器，每台服务器都可以执行任务。每台服务器都有一个唯一的 ID，即从 $1$ 到 $n$ 的整数。

已知在一天内会有 $q$ 个任务到来，第 $i$ 个任务的特征由三个整数表示：$t_{i}$ 表示任务到来的时刻（单位：秒），$k_{i}$ 表示执行该任务所需的服务器数量，$d_{i}$ 表示执行该任务所需的时间（单位：秒）。所有的 $t_{i}$ 都是不同的。

要执行第 $i$ 个任务，需要在第 $t_{i}$ 秒时找到 $k_{i}$ 台空闲的服务器。当服务器开始执行任务后，每台服务器将在接下来的 $d_{i}$ 秒内处于忙碌状态。因此，它们将在 $t_{i},t_{i}+1,\cdots,t_{i}+d_{i}-1$ 秒内忙碌。为了执行任务，将从所有空闲的服务器中选择 ID 最小的 $k_{i}$ 台服务器。如果在第 $t_{i}$ 秒时没有足够的空闲服务器，则该任务将被忽略。

编写一个程序，确定哪些任务将被执行，哪些任务将被忽略。

#### 说明/提示
在第一个样例中，在第 $1$ 秒时，第一个任务到来，它将在 ID 为 $1$、$2$ 和 $3$ 的服务器上执行（ID 之和为 $6$），持续两秒。在第 $2$ 秒时，第二个任务到来，它将被忽略，因为在该秒只有服务器 $4$ 是空闲的。在第 $3$ 秒时，第三个任务到来。此时，ID 为 $1$、$2$ 和 $3$ 的服务器又空闲了，因此第三个任务将在所有 ID 为 $1$、$2$、$3$ 和 $4$ 的服务器上执行（ID 之和为 $10$）。

在第二个样例中，在第 $3$ 秒时，第一个任务到来，它将在 ID 为 $1$ 和 $2$ 的服务器上执行（ID 之和为 $3$），持续三秒。在第 $5$ 秒时，第二个任务到来，它将在服务器 $3$ 上执行，因为前两个服务器正在忙于执行第一个任务。

#### 样例 #1
##### 输入
```
4 3
1 3 2
2 2 1
3 4 3
```
##### 输出
```
6
-1
10
```

#### 样例 #2
##### 输入
```
3 2
3 2 3
5 1 2
```
##### 输出
```
3
3
```

#### 样例 #3
##### 输入
```
8 6
1 3 20
4 2 1
6 5 5
10 1 1
15 3 6
21 8 8
```
##### 输出
```
6
9
30
-1
15
36
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟任务分配的过程。通过记录每台服务器的空闲时间，对于每个任务，从 ID 最小的服务器开始检查是否空闲，若空闲则选择该服务器，直到选够所需数量或没有足够的空闲服务器。若选够则更新所选服务器的空闲时间并输出服务器 ID 之和，否则输出 -1。

不同题解的主要区别在于数据结构的选择和代码实现细节。部分题解使用数组直接记录服务器的空闲时间，部分使用结构体和 `vector` ，还有使用优先队列进行优化。

### 所选题解
- **作者：封禁用户**（4星）
  - 关键亮点：使用结构体和 `vector` 存储服务器信息，通过自定义比较函数对服务器按空闲时间和 ID 排序，代码逻辑清晰。
- **作者：XCH_0803**（4星）
  - 关键亮点：使用简单的数组记录服务器可用时间，模拟过程简洁明了，代码可读性高。
- **作者：IcyFoxer_XZY**（4星）
  - 关键亮点：思路清晰，代码简洁，通过数组记录服务器结束任务的时间，实现任务分配的模拟。

### 重点代码
#### 作者：封禁用户
```cpp
struct Node{
    int value, pos;
    bool operator<(const Node &tmp) const{
        if (tmp.pos != pos) return pos > tmp.pos;
        else return value > tmp.value;
    };
    Node(int x, int y):value(x), pos(y){};
    Node(){};
}node[114514];

int main(){
    int n,q;
    cin>>n>>q;
    vector<Node> s(n);
    for (int i = 0; i < n; ++i) s[i] = Node(i + 1, 0);
    while (q--) {
        int c, need, t;
        scanf("%d%d%d", &c, &need, &t);
        vector<Node> re;
        for (int i = 0; i < s.size() && re.size() < need; ++i){
            if (s[i].pos <= c) re.push_back(s[i]);
        }
        if (re.size() == need) {
            int ans = 0;
            for (int i = 0; i < re.size(); ++i) {
                ans += re[i].value;
                re[i].pos = c + t;
            }
            cout << ans << endl;
        }
        else  cout << -1 << endl;
        for (int i = 0; i < re.size(); ++i) s[re[i].value - 1].pos = re[i].pos;
    }
    return 0;
}
```
核心实现思想：使用结构体 `Node` 存储服务器的 ID 和空闲时间，通过 `vector` 存储所有服务器信息。对于每个任务，遍历服务器，将空闲的服务器加入 `re` 中，若 `re` 中的服务器数量满足任务需求，则更新服务器的空闲时间并输出 ID 之和，否则输出 -1。

#### 作者：XCH_0803
```c
int a[200];
int main(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=q;i++){
        int t,k,d;
        cin>>t>>k>>d;
        int t1=t+d;
        int cnt=0,sum=0;
        for(int j=1;j<=n;j++){
            if(a[j]<=t){
                cnt++;
                sum+=j;
                if(cnt>=k){
                    break;
                }
            }
        }
        if(cnt<k){
            cout<<"-1"<<endl;
        }
        else{
            for(int j=1;j<=n;j++){
                if(a[j]<=t&&cnt>0){
                    a[j]=t1;
                    cnt--;
                }
            }
            cout<<sum<<endl;
        }
    }
    return 0;
}
```
核心实现思想：使用数组 `a` 记录服务器的可用时间，对于每个任务，遍历服务器，统计空闲服务器数量并计算 ID 之和，若空闲服务器数量满足任务需求，则更新服务器的可用时间并输出 ID 之和，否则输出 -1。

#### 作者：IcyFoxer_XZY
```cpp
int n,q,t,k,d,w[105],s,cnt;
int main(){
    scanf("%d%d",&n,&q);
    while(q--){
        s=0,cnt=0;
        scanf("%d%d%d",&t,&k,&d);
        for(register int i=1;i<=n&&cnt<k;++i)
            if(w[i]<t){
                ++cnt;
                s+=i;
            }   
        if(cnt<k)puts("-1");
        else{
            printf("%d\n",s);
            for(register int i=1;i<=n&&cnt;++i)
                if(w[i]<t){
                    --cnt;
                    w[i]=t+d-1;
                }
        }
    }
    return 0;
}
```
核心实现思想：使用数组 `w` 记录服务器结束任务的时间，对于每个任务，遍历服务器，统计空闲服务器数量并计算 ID 之和，若空闲服务器数量满足任务需求，则更新服务器的结束任务时间并输出 ID 之和，否则输出 -1。

### 最优关键思路或技巧
- 使用数组记录服务器的空闲时间或结束任务时间，方便判断服务器是否可用。
- 从 ID 最小的服务器开始遍历，确保选择的是 ID 最小的空闲服务器。

### 拓展思路
同类型题或类似算法套路：其他资源分配问题，如会议室安排、车辆调度等，都可以使用类似的模拟方法解决。

### 推荐洛谷题目
- P1098 字符串的展开
- P1160 队列安排
- P1223 排队接水

### 个人心得
- **作者：nj_peak**：在编写代码时，要注意变量的作用域，避免出现变量累加的问题。如在该题中，`ans` 变量应该在每次任务循环内部初始化，否则会导致输出结果错误。 

---
处理用时：55.24秒