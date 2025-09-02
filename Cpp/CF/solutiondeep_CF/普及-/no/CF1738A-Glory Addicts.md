# 题目信息

# Glory Addicts

## 题目描述

The hero is addicted to glory, and is fighting against a monster.

The hero has $ n $ skills. The $ i $ -th skill is of type $ a_i $ (either fire or frost) and has initial damage $ b_i $ .

The hero can perform all of the $ n $ skills in any order (with each skill performed exactly once). When performing each skill, the hero can play a magic as follows:

- If the current skill immediately follows another skill of a different type, then its damage is doubled.

 In other words, 1. If a skill of type fire and with initial damage $ c $ is performed immediately after a skill of type fire, then it will deal $ c $ damage;
2. If a skill of type fire and with initial damage $ c $ is performed immediately after a skill of type frost, then it will deal $ 2c $ damage;
3. If a skill of type frost and with initial damage $ c $ is performed immediately after a skill of type fire, then it will deal $ 2c $ damage;
4. If a skill of type frost and with initial damage $ c $ is performed immediately after a skill of type frost , then it will deal $ c $ damage.

Your task is to find the maximum damage the hero can deal.

## 说明/提示

In the first test case, we can order the skills by $ [3, 1, 4, 2] $ , and the total damage is $ 100 + 2 \times 1 + 2 \times 1000 + 10 = 2112 $ .

In the second test case, we can order the skills by $ [1, 4, 2, 5, 3, 6] $ , and the total damage is $ 3 + 2 \times 6 + 2 \times 4 + 2 \times 7 + 2 \times 5 + 2 \times 8 = 63 $ .

In the third test case, we can order the skills by $ [1, 2, 3] $ , and the total damage is $ 1000000000 + 1000000000 + 1000000000 = 3000000000 $ .

In the fourth test case, there is only one skill with initial damage $ 1 $ , so the total damage is $ 1 $ .

## 样例 #1

### 输入

```
4
4
0 1 1 1
1 10 100 1000
6
0 0 0 1 1 1
3 4 5 6 7 8
3
1 1 1
1000000000 1000000000 1000000000
1
1
1```

### 输出

```
2112
63
3000000000
1```

# AI分析结果

### 题目内容
# 荣耀成瘾者

## 题目描述
这位英雄痴迷于荣耀，正在与一只怪物战斗。

这位英雄有 $n$ 个技能。第 $i$ 个技能的类型为 $a_i$（火或冰），初始伤害为 $b_i$。

这位英雄可以按照任意顺序施展所有 $n$ 个技能（每个技能恰好施展一次）。在施展每个技能时，这位英雄可以如下施展魔法：
 - 如果当前技能紧跟在另一个不同类型的技能之后，那么它的伤害翻倍。

 换句话说，1. 如果一个类型为火且初始伤害为 $c$ 的技能紧跟在一个类型为火的技能之后施展，那么它造成 $c$ 的伤害；
 2. 如果一个类型为火且初始伤害为 $c$ 的技能紧跟在一个类型为冰的技能之后施展，那么它造成 $2c$ 的伤害；
 3. 如果一个类型为冰且初始伤害为 $c$ 的技能紧跟在一个类型为火的技能之后施展，那么它造成 $2c$ 的伤害；
 4. 如果一个类型为冰且初始伤害为 $c$ 的技能紧跟在一个类型为冰的技能之后施展，那么它造成 $c$ 的伤害。

你的任务是找出这位英雄能造成的最大伤害。

## 说明/提示
在第一个测试用例中，我们可以按 $[3, 1, 4, 2]$ 的顺序排列技能，总伤害为 $100 + 2×1 + 2×1000 + 10 = 2112$。

在第二个测试用例中，我们可以按 $[1, 4, 2, 5, 3, 6]$ 的顺序排列技能，总伤害为 $3 + 2×6 + 2×4 + 2×7 + 2×5 + 2×8 = 63$。

在第三个测试用例中，我们可以按 $[1, 2, 3]$ 的顺序排列技能，总伤害为 $1000000000 + 1000000000 + 1000000000 = 3000000000$。

在第四个测试用例中，只有一个初始伤害为 $1$ 的技能，所以总伤害为 $1$。

## 样例 #1
### 输入
```
4
4
0 1 1 1
1 10 100 1000
6
0 0 0 1 1 1
3 4 5 6 7 8
3
1 1 1
1000000000 1000000000 1000000000
1
1
1
```
### 输出
```
2112
63
3000000000
1
```
### 算法分类
贪心

### 题解综合分析与结论
所有题解都采用贪心策略，核心思路是根据两种技能数量的不同情况，合理安排技能释放顺序，使高伤害技能尽可能获得双倍伤害。主要差异在于实现细节和代码风格。思路上，都先对技能按属性分类，再排序处理；算法要点是根据技能数量关系确定释放顺序及计算伤害；难点在于处理第一个技能无法双倍伤害以及数量不同时如何保证总伤害最大，各题解均通过分类讨论和排序来解决。

### 所选的题解
- **作者：yitian_ (5星)**
    - **关键亮点**：思路清晰，代码简洁明了，详细注释便于理解。对三种技能数量关系（大于、小于、等于）分别进行处理，逻辑严谨。
    - **重点代码核心实现思想**：先读入技能属性和伤害，分别存入对应数组并排序，再根据技能数量差决定先释放哪些技能，最后计算总伤害。
```c
#include<bits/stdc++.h>
using namespace std;

int a[200010],b[200010]; 
int atr[200010]; 

int main()
{
    int t;
    cin >> t;
    while(t--)
	{
        int n;
	    cin >> n;
	    long long ans=0; 
	    int cnta=0,cntb=0; 
	    for(int i=1;i<=n;i++) 
	    {
	    	cin >> atr[i];
		}
		for(int i=1;i<=n;i++)
		{
			int c;
			cin >> c;
	        if(atr[i]==0)
			{
				cnta++;
	            a[cnta]=c;
	        }
	        if(atr[i]==1)
			{
				cntb++;
	            b[cntb]=c;
	        }
	    }
	    sort(a+1,a+cnta+1);
	    sort(b+1,b+cntb+1);
	    if(cnta>cntb)
		{
	        int dv=cnta-cntb;
	        for(int i=1;i<=dv;i++) ans+=a[i];
	        for(int i=dv+1;i<=cnta;i++) ans+=a[i]*2;
	        for(int i=1;i<=cntb;i++) ans+=b[i]*2;
	    }
	    else if(cntb>cnta)
		{
	        int dv=cntb-cnta;
	        for(int i=1;i<=dv;i++) ans+=b[i];
	        for(int i=dv+1;i<=cntb;i++) ans+=b[i]*2;
	        for(int i=1;i<=cnta;i++) ans+=a[i]*2;
	    }
	    else 
		{
	        for(int i=1;i<=cnta;i++) ans+=a[i]*2;
	        for(int i=1;i<=cntb;i++) ans+=b[i]*2;
	        if(a[1]<=b[1]) ans-=a[1];
	        else ans-=b[1];
	    }
	    cout << ans << endl;
    }
    return 0;
}
```
- **作者：__owowow__ (4星)**
    - **关键亮点**：代码简洁，利用 `#define` 简化代码书写，对三种情况的处理逻辑清晰。
    - **重点代码核心实现思想**：与yitian_思路类似，读入数据后分类排序，根据技能数量关系计算总伤害。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define MA 200005
#define int long long
int n,a[MA],b[MA],na,nb,t,ans,shu[MA],dam,pre;
signed main(){
    cin>>t;
    while(t--){
        cin>>n;
        ans=0,na=0,nb=0;
        for(int i=1;i<=n;i++) cin>>shu[i];
        for(int i=1;i<=n;i++){
            cin>>dam;
            if(shu[i]==0) a[++na]=dam;
            else b[++nb]=dam;
        }
        sort(a+1,a+na+1);
        sort(b+1,b+nb+1);
        if(na>nb){
            pre=na-nb;
            for(int i=1;i<=pre;i++) ans+=a[i];
            for(int i=1;i<=nb;i++) ans=ans+a[i+pre]*2+b[i]*2;
        }
        else if(nb>na){
            pre=nb-na;
            for(int i=1;i<=pre;i++) ans+=b[i];
            for(int i=1;i<=na;i++) ans=ans+b[i+pre]*2+a[i]*2;
        }
        else{
            for(int i=1;i<=na;i++) ans+=2*(a[i]+b[i]);
            ans-=min(a[1],b[1]);
        }
        cout<<ans<<endl;
    }
    return 0;
}
```
- **作者：Land_ER (4星)**
    - **关键亮点**：使用 `vector` 存储技能伤害，代码结构清晰，对技能数量不同情况的处理简洁明了。
    - **重点代码核心实现思想**：读入数据并分类存储到 `vector` 中，排序后根据技能数量关系计算总伤害。
```cpp
#include <bits/stdc++.h>
using namespace std;

vector<int> fire, frost;
int a[100005], b;

void solve(void) {
    int n;
    long long int ans = 0;
    cin >> n;
    fire.clear();
    frost.clear();
    for(int i = 0; i < n; ++ i)
        cin >> a[i];
    for(int i = 0; i < n; ++ i) {
        cin >> b;
        ans += 2ll * b;
        if(!a[i])
            fire.push_back(b);
        else
            frost.push_back(b);
    }
        
    if(fire.size() < frost.size())
        swap(fire, frost);
    sort(fire.begin(), fire.end());
    sort(frost.begin(), frost.end());

    if(fire.size() == frost.size())
        ans -= min(fire[0], frost[0]);
    else
        for(int i = 0, s = fire.size() - frost.size(); i < s; ++ i)
            ans -= fire[i];
        
    printf("%lld\n", ans);

    return;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t --) {
        solve();
    }
    return 0;
}
```

### 最优关键思路或技巧
1. **分类讨论与贪心策略**：根据两种技能数量的大小关系进行分类讨论，优先让伤害高的技能获得双倍伤害，以达到总伤害最大化。
2. **排序**：对不同属性技能的伤害值进行排序，方便按贪心策略选取技能，实现最优释放顺序。

### 同类型题或类似算法套路拓展
同类型题目通常围绕如何通过合理安排元素顺序，利用某种条件（如相邻元素关系）来最大化或最小化某个目标值。类似算法套路是先分析题目条件，确定贪心策略，再通过排序、分类讨论等方式实现。例如在一些任务调度问题中，根据任务的不同属性（如执行时间、收益等）和任务间的依赖关系，合理安排任务顺序以获取最大收益。

### 洛谷相似题目推荐
1. **P1080 [NOIP2012 提高组] 国王游戏**：通过对数据进行排序，利用贪心策略解决分配问题，与本题通过排序和贪心确定技能释放顺序以最大化伤害类似。
2. **P1248 加工生产调度**：同样是通过合理安排顺序来优化目标值，涉及到贪心思想的运用，与本题思路有相似之处。
3. **P2123 皇后游戏**：基于排序和贪心策略，根据人物的不同属性安排顺序以最小化总时间，和本题确定技能释放顺序的思路类似。 

---
处理用时：71.18秒