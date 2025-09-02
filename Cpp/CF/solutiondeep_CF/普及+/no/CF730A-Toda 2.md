# 题目信息

# Toda 2

## 题目描述

A group of $ n $ friends enjoys playing popular video game Toda 2. There is a rating system describing skill level of each player, initially the rating of the $ i $ -th friend is $ r_{i} $ .

The friends decided to take part in the championship as a team. But they should have equal ratings to be allowed to compose a single team consisting of all $ n $ friends. So the friends are faced with the problem: how to make all their ratings equal.

One way to change ratings is to willingly lose in some matches. Friends can form a party consisting of two to five (but not more than $ n $ ) friends and play a match in the game. When the party loses, the rating of each of its members decreases by $ 1 $ . A rating can't become negative, so $ r_{i}=0 $ doesn't change after losing.

The friends can take part in multiple matches, each time making a party from any subset of friends (but remember about constraints on party size: from $ 2 $ to $ 5 $ members).

The friends want to make their ratings equal but as high as possible.

Help the friends develop a strategy of losing the matches so that all their ratings become equal and the resulting rating is maximum possible.

## 样例 #1

### 输入

```
5
4 5 1 7 4
```

### 输出

```
1
8
01010
00011
01010
10010
00011
11000
00011
11000
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
0
2
11
11
```

## 样例 #3

### 输入

```
3
1 1 1
```

### 输出

```
1
0
```

# AI分析结果

### 题目内容
# Toda 2

## 题目描述
有n个朋友喜欢玩热门电子游戏Toda 2。游戏中有一个评级系统来描述每个玩家的技能水平，最初第i个朋友的评级为$r_{i}$。

朋友们决定组队参加锦标赛。但为了能组成一个包含所有n个朋友的队伍，他们的评级必须相等。因此，朋友们面临一个问题：如何使他们所有的评级都相等。

改变评级的一种方法是故意在某些比赛中失败。朋友们可以组成一个由2到5人（但不超过n人）组成的小队并在游戏中进行一场比赛。当小队失败时，其每个成员的评级会降低1。评级不能变为负数，所以当$r_{i}=0$时，失败后评级不会改变。

朋友们可以参加多场比赛，每次从小队中任意选择一个子集组成小队（但要记住小队人数的限制：2到5人）。

朋友们希望使他们的评级相等，并且这个相等的评级尽可能高。

帮助朋友们制定一个输掉比赛的策略，使得他们所有的评级都相等，并且最终的评级尽可能高。

## 样例 #1
### 输入
```
5
4 5 1 7 4
```
### 输出
```
1
8
01010
00011
01010
10010
00011
11000
00011
11000
```

## 样例 #2
### 输入
```
2
1 2
```
### 输出
```
0
2
11
11
```

## 样例 #3
### 输入
```
3
1 1 1
```
### 输出
```
1
0
```

### 算法分类
贪心

### 综合分析与结论
这三道题解思路基本一致，都采用贪心策略，利用优先队列维护当前最大值及其相关信息。核心在于每次操作都对当前序列中的最大值进行处理，并且由于操作区间长度为2到5，将4和5拆分为2 + 2和2 + 3，简化为每次选择2个或3个数字减1的操作。难点在于如何决定每次选择2个还是3个数字，题解均通过判断最大值的个数的奇偶性来决定：若最大值个数为偶数，选择2个最大值操作；若为奇数（除1外），选择3个最大值操作；若最大值个数为1，则选择最大值与第二大值操作。这样能保证在使所有数字相等的同时，最终相等的数值最大。

### 所选的题解
- **作者：liwenxi114514 (5星)**
    - **关键亮点**：思路清晰，代码简洁，对优先队列的使用较为熟练，详细记录每次操作并输出结果。
    - **核心代码片段**：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[105];
bool ans[10005][105];
priority_queue<pair<int,int> > q;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        q.push({a[i],i});//记录数值与位置，记录位置是为了统计操作
    }
    int sum=1;//操作次数
    while(1){
        pair<int,int> x=q.top();
        q.pop();
        pair<int,int> y=q.top();
        q.pop();
        if(q.empty()){
            if(x.first==y.first){
                cout<<x.first<<"\n";
                break;
            }
        }
        if(x.first==y.first){
            queue<pair<int,int> > q1;//记录弹出的值
            bool flag=0;
            int sss=2;//最大数个数
            while(!q.empty()){
                pair<int,int> z=q.top();
                q.pop();
                q1.push(z);
                if(z.first!=x.first){
                    flag=1;
                    break;
                }
                sss++;
            }
            if(!flag){//所有数都相同
                cout<<x.first<<"\n";//输出答案
                break;
            }
            sss=sss%2;//由于最后会加入两个数，所以目前只需要加sss%2个数
            while(!q1.empty()){//将弹出的值加回来
                if(q1.front().first==x.first&&sss>0){//与最大值相同
                    q.push({max(q1.front().first-1,0ll),q1.front().second});
                    ans[sum][q1.front().second]=1;
                }else{
                    q.push({q1.front().first,q1.front().second});
                }
                q1.pop();
                sss--;
            }
        }
        ans[sum][x.second]=ans[sum][y.second]=1;//统计答案
        sum++;
        q.push({max(x.first-1,0ll),x.second});
        q.push({max(y.first-1,0ll),y.second});
    }
    cout<<sum-1<<"\n";
    for(int i=1;i<sum;i++){
        for(int j=1;j<=n;j++){
            cout<<ans[i][j];
        }
        cout<<"\n";
    }
    return 0;
}
```
核心实现思想：每次从优先队列取出两个最大值，判断所有数是否已相等，若未相等则根据最大值个数的奇偶性决定后续操作，并记录每次操作涉及的位置。

- **作者：Erica_N_Contina (5星)**
    - **关键亮点**：代码注释详细，对贪心策略的每一步解释清晰，将操作封装成函数，结构清晰。
    - **核心代码片段**：
```cpp
void dec1(){//再选择1个数字 
    int v2=pq.top().pf,id2=pq.top().ps;
    pq.pop();
    pq.push(mp(max(v2-1,0ll),id2));
    pq.push(mp(max(v-1,0ll),id));
    
    ton[v]--;ton[max(v-1,0ll)]++;
    ton[v2]--;ton[max(v2-1,0ll)]++;
    out(id,id2,0);
    
}

void dec2(){//再选择2个数字 
    int v2=pq.top().pf,id2=pq.top().ps;
    pq.pop();
    int v3=pq.top().pf,id3=pq.top().ps;
    pq.pop();
    pq.push(mp(max(v3-1,0ll),id3));
    pq.push(mp(max(v2-1,0ll),id2));
    pq.push(mp(max(v-1,0ll),id));
    
    ton[v]--;ton[max(v-1,0ll)]++;
    ton[v3]--;ton[max(v3-1,0ll)]++;
    ton[v2]--;ton[max(v2-1,0ll)]++;
    out(id,id2,id3);
}

signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>v;
        ton[v]++;
        pq.push(mp(v,i));
    } 
    while(1){
        v=pq.top().pf,id=pq.top().ps;//先选择1个数字 
        pq.pop();
        
        if(ton[v]==n){
            cout<<v<<endl;
            break;
        }
        
        if(ton[v]==1){
            dec1();
            
        }else if(ton[v]%2){
            dec2();
        }else{
            dec1();
        }
    }
    // 输出部分省略
    return 0;
}
```
核心实现思想：将选择2个或3个数字减1的操作封装成函数，在主函数中根据最大值个数的奇偶性调用相应函数进行操作。

- **作者：chengni (4星)**
    - **关键亮点**：详细展示了利用优先队列实现贪心策略的过程，对每种情况的处理逻辑清晰。
    - **核心代码片段**：
```cpp
for(int j=1;;j++){
    int num=1,cnt=1;
    a[cnt]=q.top();q.pop();
    while(q.size()){
        if(q.top().v==a[1].v){//计算最大值的个数
            cnt++;
            a[cnt]=q.top();
            q.pop();
        }
        else break;
    }
    if(cnt==n){//为n，结束
        printf("%d\n",a[cnt].v);
        printf("%d\n",j-1);
        // 输出方案部分省略
        return 0;
    }
    else if(cnt==1){//为1，取第二大值
        node v=q.top();//第二大
        q.pop();
        v.v-=1;
        if(v.v<0) v.v=0;
        f[j][v.f]=1;
        q.push(v);
        a[cnt].v-=1;
        if(a[cnt].v<0) a[cnt].v=0;
        f[j][a[cnt].f]=1;
        q.push(a[cnt]);
    }
    else if(cnt%2==0){//为偶数，处理两个最大值
        for(int i=3;i<=cnt;i++){//多余的扔回去
            q.push(a[i]);
        }
        a[1].v-=1;
        if(a[1].v<0) a[1].v=0;
        f[j][a[1].f]=1;
        q.push(a[1]);
        a[2].v-=1;
        if(a[2].v<0) a[2].v=0;
        f[j][a[2].f]=1;
        q.push(a[2]);
    }
    else {//为奇数且不为1，处理前三个
        for(int i=4;i<=cnt;i++){//多余的扔回去
            q.push(a[i]);
        }
        a[1].v-=1;
        if(a[1].v<0) a[1].v=0;
        f[j][a[1].f]=1;
        q.push(a[1]);
        a[2].v-=1;
        if(a[2].v<0) a[2].v=0;
        f[j][a[2].f]=1;
        q.push(a[2]);
        a[3].v-=1;
        if(a[3].v<0) a[3].v=0;
        f[j][a[3].f]=1;
        q.push(a[3]);
    }
    
} 
```
核心实现思想：每次循环计算最大值的个数，根据个数的不同情况分别处理，将处理后的值重新加入优先队列。

### 最优关键思路或技巧
利用优先队列维护当前最大值及其位置信息，通过贪心策略，根据最大值个数的奇偶性选择2个或3个最大值进行减1操作，保证最终相等的评级尽可能高。

### 拓展
此类题目属于贪心策略在数值调整问题中的应用，类似套路是在不要求操作次数最少，只关注最终结果最优的情况下，通过合理的贪心选择策略简化问题。例如，对于一些资源分配、数值均衡等问题，如果可以通过局部最优选择达到全局最优，可尝试贪心策略。

### 洛谷相似题目
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)：同样是利用贪心策略解决分组问题，通过对数据排序后进行合理分组以满足题目要求。
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199)：需要通过分析题目条件，采用贪心策略来选择最优的游戏方案。
- [P1080 国王游戏](https://www.luogu.com.cn/problem/P1080)：通过对数据进行排序，依据贪心策略找到最优的排列顺序以解决问题。 

---
处理用时：87.85秒