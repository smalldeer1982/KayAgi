# Renovation

## 题目描述

The mayor of the Berland city S sees the beauty differently than other city-dwellers. In particular, he does not understand at all, how antique houses can be nice-looking. So the mayor wants to demolish all ancient buildings in the city.

The city S is going to host the football championship very soon. In order to make the city beautiful, every month the Berland government provides mayor a money tranche. The money has to be spent on ancient buildings renovation.

There are $ n $ months before the championship and the $ i $ -th month tranche equals to $ a_{i} $ burles. The city S has $ m $ antique buildings and the renovation cost of the $ j $ -th building is $ b_{j} $ burles.

The mayor has his own plans for spending the money. As he doesn't like antique buildings he wants to demolish as much of them as possible. For the $ j $ -th building he calculated its demolishing cost $ p_{j} $ .

The mayor decided to act according to the following plan.

Each month he chooses several (possibly zero) of $ m $ buildings to demolish in such a way that renovation cost of each of them separately is not greater than the money tranche $ a_{i} $ of this month ( $ b_{j}<=a_{i} $ ) — it will allow to deceive city-dwellers that exactly this building will be renovated.

Then the mayor has to demolish all selected buildings during the current month as otherwise the dwellers will realize the deception and the plan will fail. Definitely the total demolishing cost can not exceed amount of money the mayor currently has. The mayor is not obliged to spend all the money on demolishing. If some money is left, the mayor puts it to the bank account and can use it in any subsequent month. Moreover, at any month he may choose not to demolish any buildings at all (in this case all the tranche will remain untouched and will be saved in the bank).

Your task is to calculate the maximal number of buildings the mayor can demolish.

## 说明/提示

In the third example the mayor acts as follows.

In the first month he obtains $ 6 $ burles tranche and demolishes buildings $ #2 $ (renovation cost $ 6 $ , demolishing cost $ 4 $ ) and $ #4 $ (renovation cost $ 5 $ , demolishing cost $ 2 $ ). He spends all the money on it.

After getting the second month tranche of $ 3 $ burles, the mayor selects only building $ #1 $ (renovation cost $ 3 $ , demolishing cost $ 1 $ ) for demolishing. As a result, he saves $ 2 $ burles for the next months.

In the third month he gets $ 2 $ burle tranche, but decides not to demolish any buildings at all. As a result, he has $ 2+2=4 $ burles in the bank.

This reserve will be spent on the fourth month together with the $ 4 $ -th tranche for demolishing of houses $ #3 $ and $ #5 $ (renovation cost is $ 4 $ for each, demolishing costs are $ 3 $ and $ 5 $ correspondingly). After this month his budget is empty.

Finally, after getting the last tranche of $ 3 $ burles, the mayor demolishes building $ #6 $ (renovation cost $ 2 $ , demolishing cost $ 3 $ ).

As it can be seen, he demolished all $ 6 $ buildings.

## 样例 #1

### 输入

```
2 3
2 4
6 2 3
1 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 5
5 3 1
5 2 9 1 10
4 2 1 3 10
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5 6
6 3 2 4 3
3 6 4 5 4 2
1 4 3 2 5 3
```

### 输出

```
6
```

# 题解

## 作者：比利♂海灵顿 (赞：5)

# CF883J Renovation

## 题意

共 $n$ 天，每天有 $a_i$ 经费。

有 $m$ 个房屋，每个房屋有属性 $b$，$p$。

第 $i$ 天可以拆除 $b < a_i$ 的房屋，每拆一座，会花费 $p$ 的经费。经费可以转结到下一天。

## 使 $a$ 单调

发现如果没有 $b$ 的限制，一定是第 $n$ 天统一拆除，因为将所有的经费留到第 $n$ 天，按 $p$ 从小到大拆一定能得到最优方案。

假设 $a_i < a_j$，$i < j$，在第 $i$ 天能拆的房子，在第 $j$ 天肯定能拆，所以对于这个 $i$，我们不用考虑它是否应该拆房子，只要将钱存起来就好了。

我们把可以考虑拆房子的天找出来，发现这些天 $i$ 必须满足不存在 $j > i$ 且 $a_j > a_i$。

可以从后往前 $O(n)$ 处理出这些天，存入数组 $Ava$ 中，称作 `工作日`。由于是倒着处理的，所以 $Ava_i$ 表示倒数第 $i$ 个工作日。

## 拆除

我们把所有房子按 $b$ 排序。

从前往后算，每个工作日可以拆除的房子越来越少，所以在每个工作日考虑过了今天就拆不了的房子，也就是满足 $a_{Ava_{i}} \geq b_j > a_{Ava_{i - 1}}$ 的房子 $j$。

按顺序将这些房子插入以 $p$ 为序的小根堆里，从小到大将能拆的拆掉。

每个工作日可以获得的经费是上个工作日到这个工作日之间的所有经费和当天的经费，即 $\displaystyle{\sum_{j = Ava_{i + 1} + 1}^{Ava_i}a_i}$。用前缀和可以 $O(1)$ 求出。

## 重建

发现如果按上面的算法，会在一些正确策略是前面故意攒钱到后面再花的数据中得到错误的答案。

假设还有一种操作，重建，每次重建会得到拆除它对应的经费。这个操作可以帮我们反悔。

每次拆除的时候，将拆掉的房子丢进按 $p$ 为序的大根堆，每次经费不足，但是重建一个房子再拆除不亏的时候(注意这很重要，只有 `重建 + 拆除` 两个操作结束后使经费增加才能使用)，重建获得经费最多的房子，拆除正在考虑的房子。

这样就能得到正确的答案了。

### 代码实现

```cpp
unsigned long long a[100005], Sum[100005], Now(0);
unsigned Ava[100005], Hd, m, n, Max(0), Cnt(0), Ans(0);
struct Bldi {
  unsigned long long b, p;
  inline const char operator < (const Bldi &x) const{
    return this->p > x.p; 
  } 
}B[100005];
inline char cmp (const Bldi &x, const Bldi &y) {
  return x.b < y.b;
}
priority_queue <Bldi> Q;
priority_queue <unsigned> BQ;
int main() {
  n = RD(), m = RD();
  for (register unsigned i(1); i <= n; ++i) a[i] = RD(), Sum[i] = Sum[i - 1] + a[i]; 
  for (register unsigned i(1); i <= m; ++i) B[i].b = RD();
  for (register unsigned i(1); i <= m; ++i) B[i].p = RD();
  sort(B + 1, B + m + 1, cmp);
  for (register unsigned i(n); i; --i) {
    if(a[i] > Max) {
      Ava[++Cnt] = i;
      Max = a[i];
    }
  }
  Ava[Cnt + 1] = 0;
  B[m + 1].p = 0x3f3f3f3f3f3f3f3f, Hd = m, Q.push(B[m + 1]);
  BQ.push(0);
  for (register unsigned i(Cnt); i; --i) {
    while (Hd && (B[Hd].b > a[Ava[i - 1]])) {
      Q.push(B[Hd--]);
    }
    Now += Sum[Ava[i]] - Sum[Ava[i + 1]];
    while ((Q.top().p <= Now) || (Q.top().p < BQ.top())) {
      if(Q.top().b > a[Ava[i]]) {
        Q.pop();
        continue;
      }
      if(Q.top().p > Now) {
        Now += BQ.top(), BQ.pop(), --Ans; 
      }
      ++Ans;
      Now -= Q.top().p;
      BQ.push(Q.top().p);
      Q.pop(); 
    }
  }
  printf("%u\n", Ans);
  return Wild_Donkey;
}
```

---

## 作者：Llx2022 (赞：4)

# 题意

___


有 $n$ 天，每天可获得钱  $a_i$  

有 $m$ 个建筑，每个建筑有估算费用 $b_j$  和实际拆毁费用 $p_j$ 

问：  **当且仅当**   $a_{i}$  $\geq$ $b_j$  可以拆除,最多可以拆毁几个建筑?

 注意：估算费用不一定是满足一定大于等于实际拆毁费用的。

 ___

# 输入

___

-  **n** 天 **m** 个建筑

-  第 **i** 天可获得的经费 $a_i$

-  第 **j** 个建筑估算费用 $b_j$

-  第 **j** 个建筑实际拆毁费用 $p_j$

___


# 思路


___


通过思考，这个题因该显然是 **贪心**，所以我们要找到贪心策略。( why :  因为最终的答案一定是通过局部最优解所推得的全局最优解）

**先思考一个角度**
若考虑每天拆哪些建筑，并不容易实现，因为受预算和估测值的制约, **所以果断放弃该角度** 。

**换一个思路** ，考虑每个建筑在哪一天被拆。
**首先** 考虑第 $j$ 个建筑什么时候可以被拆,不考虑之前已经花费的钱数。
因此，当且仅当 $a_k$ $\geq$ $b_j$ 时，可以在第 $k$ 天拆，从而得出第 $j$ 个建筑可被拆除的时间是,满足 $a_k$ $\geq$ $b_j$ 条件的所有天。 
**进一步理解** ，对于第 $j$ 个建筑，我们只要在满足    $a_k$  $\geq$ $b_j$ 的最大的k那一天去考虑是否要拆它就行了,
因为如果还存在一个 $k_2$ 满足 $a_{k_2}$ $\geq$ $b_j$ ,并且 $k_2$ $<$ $k$ ,显然在 $k_2$ 那一天拆不如在 $k$ 这一天拆。因为不拆的话，可以把 ${p_j}$ 的钱省到第 $k$ 天来拆,选择 $k$ 不会比选择 $k_2$ 更差。


**如果在第  $k$  天有很多符合条件的建筑可以拆，怎么选择？**  显然是选择 $p_j$ 最小的拆掉。


**如果第 $k$ 天还有钱多怎么处理？** 
显然第 $k$ 天的钱只能用在第 $k$ ~$n$ 天，对于前 $k-1$ 天都是不能用的。那么我们就可以倒着枚举每一天钱往哪花。

#### 则 **贪心策略** 应是：对于一个建筑 $j$ 放在 $a_k$ $\geq$  $b_j$ 对应的 $day_{max_{isk}}$ （即最大的天是k）拆，若钱不足以全部拆除满足 $day_{max_{isk}}$ 号的建筑，拆最小的满足 $a_k$ $\geq$ $b_j$ 的最小 $p_j$ ，若仍有剩余处理其他的满足该条件的建筑。
**代码思路** ：
每一天都把当天能用的钱（不一定能直接拆毁）的建筑加入一个小跟堆里。每次从堆中取出 $p$ 最小的建筑拆毁,堆中 $p$ 最小的建筑也无法拆毁，加入还剩 $v$ 的钱，那么就把这些钱都投入到这个建筑中，把  $p$ 赋值为   $p-v$ 这样做的意义实际上就是为这个建筑攒 $ν$ 的钱，为了能在某一天把它拆毁掉。
___
# 代码实现
```cpp
int n,m,mx,tot,ans;
int a[N],b[N],p[N];
//less 是大根堆 greater是小根堆
//而priority_queue默认是大根堆
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>> > q;
vector<pair<int,int>> s;
int main(){
    read(n),read(m);
    for(int i=1;i<=n;i++) read(a[i]);
    for(int i=1;i<=m;i++) read(b[i]),s.push_back(make_pair(b[i],i));
    for(int i=1;i<=m;i++) read(p[i]);
    sort(s.begin(),s.end());
    //逆序相当于对于一个建筑j放在该建筑对应的最大的天数k拆
    for(int i=n;i>=1;i--){
        mx=max(mx,a[i]);
        //按建筑估算费用从小到大，把实际费用放到在堆里
        while(tot<s.size()&&s[tot].first<=mx){
            int x=s[tot].second;
            q.push(make_pair(p[x],x));
            tot++;
        }
        //每次从堆中取出p最小的建筑拆毁
        while(!q.empty()&&a[i]>=q.top().first){
            ans++;
            a[i]-=q.top().first;
            q.pop();
        }
        //堆中 p 最小的建筑也无法拆毁，加入还剩v的钱，那么就把这些钱都投入到这个建筑中，把 p 赋值为p-v这样做的意义实际上就是为这个建筑攒ν的钱，为了能在某一天把它拆毁掉。
        if(!q.empty()){
            pair<int,int> u=q.top();
            q.pop();
            u.first-=a[i];
            q.push(u);
        }
    }
    write(ans);
    return 0;
}
```



---

