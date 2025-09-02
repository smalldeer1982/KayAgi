# [GCJ 2020 #3] Pen Testing

## 题目描述

你有 $N$ 支圆珠笔。已知每支笔的墨水单位数都是 $0$ 到 $N-1$ 之间互不相同的整数，但这些笔是随机顺序给你的，因此你不知道哪支笔对应多少墨水。

你即将前往南极（那里没有笔），而你的行李只能装两支笔。你知道需要写很多重要的明信片，因此选择的两支笔的墨水总量必须至少为 $N$ 单位。

获取笔信息的唯一方法是选择一支笔尝试写字。尝试结果有两种：成功（该笔墨水减少 1 单位，可能用完）或失败（该笔已无墨水）。你可以重复测试同一支笔或不同笔。

最终，你必须选择两支笔带去南极。若这两支笔剩余墨水的总量不少于 $N$ 单位，则视为成功。

本题包含 $T$ 个测试用例，你需要在至少 $C$ 个用例中成功。注意本题所有测试集都是可见的。

### 交互协议

这是一个交互题。

初始时，你的程序应读取一行包含三个整数 $\mathbf{T}$、$\mathbf{N}$ 和 $\mathbf{C}$：测试用例数量、笔的数量和需要成功的最少用例数。（注意 $\mathbf{N}$ 在所有测试集中相同，详见数据范围部分。）

然后，你的程序需要同时处理所有 $\mathbf{T}$ 个测试用例（这是为了减少交互次数）。交互以轮次进行。

每轮开始时，你的程序需输出一行 $\mathbf{T}$ 个整数：第 $i$ 个整数表示在第 $i$ 个测试用例中要测试的笔编号（1 到 $\mathbf{N}$），若该轮不测试则输出 0。

注意：如果在每个整数后立即刷新输出缓冲区（而非整行输出后刷新），可能导致超时错误。

评测机将返回一行 $\mathbf{T}$ 个整数：第 $i$ 个整数表示该轮第 $i$ 个测试用例的耗墨量。1 表示测试成功（耗墨 1 单位），0 表示测试失败（笔已无墨）或未测试。

最多可进行 $\mathbf{N} \times (\mathbf{N}+1)/2$ 轮交互（足以耗尽所有墨水）。

当准备提交答案时，输出一行包含 $\mathbf{T}$ 个 0。此行不计入交互轮次限制，评测机不会回复。

接着输出一行 $2 \times \mathbf{T}$ 个整数：第 $(2i-1)$ 和第 $2i$ 个整数表示第 $i$ 个测试用例选择的两支笔编号。输出后程序应立即终止。

若评测机收到意外输出，将返回 -1 并终止交互。程序需及时退出以避免超时错误。

注意：每次提交时，笔的初始顺序都是独立随机生成的。

## 说明/提示

**样例解释**

交互过程解析：

```
// 读取 T=2, N=5, C=1
t, n, c = readline_int_list()
// 评测机秘密生成墨水分布：
// 测试用例1: [2,0,4,1,3]
// 测试用例2: [1,3,2,4,0]
// 第一轮：测试用例1用笔4，测试用例2用笔5
printline 4 5
// 返回1 0（笔4有墨，笔5无墨）
a1, a2 = readline_int_list()
// 第二轮：测试用例1用笔4，测试用例2用笔3
printline 4 3
// 返回0 1（笔4已无墨，笔3有墨）
a1, a2 = readline_int_list()
// 第三轮：仅测试用例2用笔2
printline 0 2
// 返回0 1
a1, a2 = readline_int_list()
// 准备提交答案
printline 0 0
// 选择笔3和笔4
printline 3 4 3 4
// 测试用例1：4+0<5（失败）
// 测试用例2：1+4≥5（成功）
// 成功数1≥C，通过
exit
```

可使用本地测试工具进行调试。建议配合[交互运行器](https://storage.googleapis.com/coding-competitions.appspot.com/interactive_runner.py)使用。注意测试工具与真实评测系统可能存在差异。

**数据范围**

- $\mathbf{N} = 15$

**测试集 1（6 分，可见判定）**

- $\mathbf{T} = 20000$
- $\mathbf{C} = 10900$（$\mathbf{C} = 0.545 \times \mathbf{T}$）

**测试集 2（11 分，可见判定）**

- $\mathbf{T} = 20000$
- $\mathbf{C} = 12000$（$\mathbf{C} = 0.6 \times \mathbf{T}$）

**测试集 3（15 分，可见判定）**

- $\mathbf{T} = 100000$
- $\mathbf{C} = 63600$（$\mathbf{C} = 0.636 \times \mathbf{T}$）

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
2 5 1

1 0

0 1

0 1```

### 输出

```

4 5

4 3

0 2

0 0
3 4 3 4```

# 题解

## 作者：FFTotoro (赞：2)

很牛的题目。学了官方题解的做法。

观察到如下的一种策略：先从左到右尝试将所有的笔都测试一遍，这样就能筛掉墨水量为 $0$ 的笔，一旦筛出墨水量为 $0$ 的笔就忽略剩下的笔进入下一个阶段；再从左到右尝试将所有的笔都不断测试，直到该笔被测试的总次数（即包含之前阶段的测试数）$\ge 2$，这样就能筛掉墨水量为 $1$ 的笔，同理一旦筛出墨水量为 $1$ 的笔就忽略剩下的笔进入下一个阶段……直到筛掉墨水量为 $K$ 的笔（$K$ 是你自己设定的一个常数），接着在没有被筛掉的笔中选择两支被测试次数最少的笔带走。

注意到 $K$ 的数值可以根据交互库返回的信息更改以获得更高的正确率，于是考虑 DP 搜索出决策树。

设状态 $f_{i,s}$，其中 $i(0\le i\le n-1)$ 表示当前已经筛掉了墨水量为 $[0,i)$ 的笔，$s$ 为一个长为 $n-i$ 的非负整数序列，表示没有被筛掉的笔从左到右被测试次数分别为 $s_1,s_2,\ldots,s_{n-i}$。状态转移：

- 边界情况为 $f_{n-1,*}=0$，否则考虑如下转移；
- 设变量 $\mathrm{pc}$ 表示考虑继续筛掉墨水量为 $i$ 的笔的最大正确率，枚举该笔所在的位置 $p$，在它之前的笔被测试次数全部变为 $i+1$，在它后面的笔被测试次数不变，它本身对应的元素被删除，从而得出序列 $s'=\{i+1,i+1,\ldots,i+1,s_{p+1},s_{p+2},\ldots,s_{n-i}\}$，$\mathrm{pc}\gets\mathrm{pc}+\dfrac{f_{i+1,s'}}{n-i}$；
- 设变量 $\mathrm{ps}$ 表示从当前的笔中直接挑选两个被测试次数最少的笔的正确率，令 $w_0,w_1$ 为被测试次数最少的两支笔的被测试次数，显然有 $\mathrm{ps}=\dfrac{\sum\limits_{x=i}^{n-2}\sum\limits_{y=x+1}^{n-1}[x+y-w_0-w_1\ge n]}{\dfrac{(n-i)(n-i-1)}{2}}$；
- $f_{i,s}=\max\{\mathrm{pc},\mathrm{ps}\}$，并根据 $\mathrm{pc}$ 和 $\mathrm{ps}$ 的大小关系决策下一步行动。

我们发现这样的 DP 状态数并不多，于是直接按照上面的方法搜决策树。令 $e=\{0,0,\ldots,0\}(|e|=n)$，计算得到 $f_{0,e}\approx 0.642$，即总体正确率约为 $64.2\%$，可以轻松通过本题。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef double db;
int main(){
  ios::sync_with_stdio(false);
  int t,n,a; cin>>t>>n>>a;
  vector<map<vector<int>,db> > mp(n-1);
  vector<set<vector<int> > > st(n-1);
  // st 存储了决策“不继续下去，直接选出两支笔”的所有状态
  auto dfs=[&](auto &&self,int l,vector<int> v)->db{
    if(l>=n-1)return 0;
    if(mp[l].find(v)!=mp[l].end())return mp[l][v];
    db pc=0,ps=0;
    for(int t=0;t<v.size();t++){
      vector<int> w;
      for(int i=0;i<t;i++)
        w.emplace_back(l+1);
      for(int i=t+1;i<v.size();i++)
        w.emplace_back(v[i]);
      pc+=self(self,l+1,w);
    }
    pc/=v.size(); // 继续筛出 i 的最大正确率
    auto w=v;
    sort(w.begin(),w.end());
    int t=0;
    for(int x=l;x<n;x++)
      for(int y=x+1;y<n;y++)
        ps+=x+y-w[0]-w[1]>=n,t++;
    ps/=t; // 直接原地选的正确率
    if(pc>ps)mp[l][v]=pc;
    else mp[l][v]=ps,st[l].emplace(v);
    // 比较两者，得出较优的方案
    return mp[l][v];
  }; // 搜决策树
  dfs(dfs,0,vector<int>(n));
  vector<int> s(t),c(t);
  // s[i] 表示第 i 组测试数据正在进行“筛出 s[i]”的阶段
  // c[i] 表示第 i 组测试数据正在考虑剩下的第 c[i] 只笔
  vector p(t,vector<int>(n)),v=p;
  // p[i] 表示第 i 组测试数据剩下的笔在原序列中的编号（从左到右）
  // v[i] 表示第 i 组测试数据剩下的笔被测试次数（从左到右）
  for(auto &i:p)iota(i.begin(),i.end(),0);
  vector<bool> f(t);
  // f[i] 表示第 i 组测试数据的求解是否结束
  while(find(f.begin(),f.end(),false)!=f.end()){
    vector<int> a(t,-1),r(t);
    for(int q=0;q<t;q++)
      if(!f[q])a[q]=p[q][c[q]];
    for(int i:a)cout<<i+1<<' ';
    cout<<endl;
    for(auto &i:r)cin>>i;
    for(int q=0;q<t;q++){
      if(f[q])continue;
      if(r[q]){
        if(++v[q][c[q]]>s[q])c[q]++;
      } // 还在本阶段，考虑下一支笔
      else{
        p[q].erase(p[q].begin()+c[q]);
        v[q].erase(v[q].begin()+c[q]);
        s[q]++;
        if(st[s[q]].find(v[q])!=st[s[q]].end())f[q]=true;
        else c[q]=0;
      } // 进入下一个阶段或直接得出答案
    }
  }
  for(int q=0;q<t;q++)
    cout<<0<<' ';
  cout<<endl;
  for(int q=0;q<t;q++){
    int x=min_element(v[q].begin(),v[q].end())-v[q].begin();
    cout<<p[q][x]+1<<' ';
    p[q].erase(p[q].begin()+x),v[q].erase(v[q].begin()+x);
    x=min_element(v[q].begin(),v[q].end())-v[q].begin();
    cout<<p[q][x]+1<<' ';
    p[q].erase(p[q].begin()+x),v[q].erase(v[q].begin()+x);
  } // 选出被测试次数最少的两支笔回答
  cout<<endl;
  return 0;
}
```

---

