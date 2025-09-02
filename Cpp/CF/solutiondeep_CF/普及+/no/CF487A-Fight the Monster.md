# 题目信息

# Fight the Monster

## 题目描述

A monster is attacking the Cyberland!

Master Yang, a braver, is going to beat the monster. Yang and the monster each have 3 attributes: hitpoints ( $ HP $ ), offensive power ( $ ATK $ ) and defensive power ( $ DEF $ ).

During the battle, every second the monster's HP decrease by $ max(0,ATK_{Y}-DEF_{M}) $ , while Yang's HP decreases by $ max(0,ATK_{M}-DEF_{Y}) $ , where index $ Y $ denotes Master Yang and index $ M $ denotes monster. Both decreases happen simultaneously Once monster's $ HP<=0 $ and the same time Master Yang's $ HP>0 $ , Master Yang wins.

Master Yang can buy attributes from the magic shop of Cyberland: $ h $ bitcoins per $ HP $ , $ a $ bitcoins per $ ATK $ , and $ d $ bitcoins per $ DEF $ .

Now Master Yang wants to know the minimum number of bitcoins he can spend in order to win.

## 说明/提示

For the first sample, prices for $ ATK $ and $ DEF $ are extremely high. Master Yang can buy $ 99 $ HP, then he can beat the monster with $ 1 $ HP left.

For the second sample, Master Yang is strong enough to beat the monster, so he doesn't need to buy anything.

## 样例 #1

### 输入

```
1 2 1
1 100 1
1 100 100
```

### 输出

```
99
```

## 样例 #2

### 输入

```
100 100 100
1 1 1
1 1 1
```

### 输出

```
0
```

# AI分析结果

### 题目内容
# 对抗怪物

## 题目描述
一只怪物正在袭击赛博之地！
勇者杨大师准备打败这只怪物。杨大师和怪物各有三个属性：生命值（$HP$）、攻击力（$ATK$）和防御力（$DEF$）。
在战斗中，每一秒怪物的生命值会减少 $max(0, ATK_Y - DEF_M)$，同时杨大师的生命值会减少 $max(0, ATK_M - DEF_Y)$，其中下标 $Y$ 表示杨大师，下标 $M$ 表示怪物。这两个减少量同时发生。一旦怪物的 $HP \leq 0$ 且杨大师的 $HP > 0$，杨大师获胜。
杨大师可以在赛博之地的魔法商店购买属性：每点生命值花费 $h$ 比特币，每点攻击力花费 $a$ 比特币，每点防御力花费 $d$ 比特币。
现在杨大师想知道，为了获胜，他最少需要花费多少比特币。

## 说明/提示
对于第一个样例，攻击力和防御力的价格极高。杨大师可以购买99点生命值，然后他可以以剩余1点生命值打败怪物。
对于第二个样例，杨大师足够强大可以打败怪物，所以他不需要购买任何东西。

## 样例 #1
### 输入
```
1 2 1
1 100 1
1 100 100
```
### 输出
```
99
```

## 样例 #2
### 输入
```
100 100 100
1 1 1
1 1 1
```
### 输出
```
0
```

### 算法分类
枚举

### 综合分析与结论
所有题解思路本质相同，均基于数据范围小的特点采用枚举法。先分析出各属性购买量的上限，再通过循环枚举所有可能的属性购买组合，判断每种组合下杨大师是否能获胜，记录能获胜的组合中的最小花费。难点在于确定合理的属性购买上限，保证枚举全面且不超时。

### 所选的题解
- **作者：CountState (5星)**
    - **关键亮点**：思路清晰，详细分析出各属性购买上限的原因，代码逻辑完整，注释清晰。
    - **核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;

int HPy,ATKy,DEFy,HPm,ATKm,DEFm,h,a,d,ans=INT_MAX;
int main(){
    cin>>HPy>>ATKy>>DEFy>>HPm>>ATKm>>DEFm>>h>>a>>d;
    for(int i=0;i<=10000;i++){
        for(int j=0;j<=200;j++){
            for(int k=0;k<=100;k++){
                bool b1=true,b2=true;
                if(ATKm-(DEFy+k)<=0) b1=false;
                if((ATKy+j)-DEFm<=0) b2=false;
                if((!b1)&&b2)  ans=min(ans,i*h+a*j+d*k);
                else if(b1&&(!b2)) continue;
                else if((!b1)&&(!b2)) continue;
                else if(floor((double)(HPy+i)/(double)(ATKm-(DEFy+k))-0.000001)>=ceil((double)HPm/(double)((ATKy+j)-DEFm))) ans=min(ans,i*h+a*j+d*k);
            }
        }
    }
    cout<<ans<<"\n";
}
```
    - **核心思想**：三层循环枚举购买的生命值、攻击力、防御力的数量，根据杨大师和怪物的攻击防御关系判断是否能获胜，更新最小花费。

- **作者：ivyjiao (5星)**
    - **关键亮点**：简洁明了地阐述了各属性购买上限的依据，代码利用GCC优化指令加速，逻辑简洁。
    - **核心代码**：
```cpp
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
using namespace std;
int ay,by,cy,am,bm,cm,a,b,c,ans=1e9;
int main(){
    cin>>ay>>by>>cy>>am>>bm>>cm>>a>>b>>c;
    for(int i=0;i<=10000;i++){
        for(int j=0;j<=200;j++){
            for(int k=0;k<=100;k++){
                int aa=ay+i,bb=by+j,cc=cy+k;
                if(bb-cm<=0) continue;
                if(bm-cc<=0) ans=min(ans,a*i+b*j+c*k);
                else if(ceil(1.0*am/(bb-cm))<ceil(1.0*aa/(bm-cc))) ans=min(ans,a*i+b*j+c*k);
            }
        }
    }
    cout<<ans;
}
```
    - **核心思想**：同样通过三层循环枚举购买属性数量，依据杨大师和怪物承受攻击轮数判断是否获胜，更新最小花费，利用GCC优化指令提升运行速度。

- **作者：_Ink (4星)**
    - **关键亮点**：详细分析取胜条件，先推导理论公式，再根据数据范围确定枚举范围，还提及可优化方向。
    - **核心代码**：
```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
#define maxn 500050
#define maxm 500050 
#define vi vector <int>
#define vvi vector <vi>
#define endl '\n'
#define ll long long
using namespace std;

void solve()
{
    int hpy, atky, defy; cin >> hpy >> atky >> defy;
    int hpm, atkm, defm; cin >> hpm >> atkm >> defm;
    int h, a, d; cin >> h >> a >> d;
    
    int ans = inf;
    for(int hi = 0; hi <= 10000; hi ++){
        for(int ai = 0; ai <= 200; ai ++){
            for(int di = 0; di <= 100; di ++){
                if(atky + ai - defm <= 0) continue;
                int thpy = hpy + hi, tatky = atky + ai, tdefy = defy + di;
                int rnd = (hpm + (tatky - defm - 1)) / (tatky - defm);
                if(rnd * (max(0, atkm - tdefy)) < thpy) ans = min(ans, hi * h + ai * a + di * d);
            }
        }
    }
    cout << ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); //cout.tie(0);
    
    int t = 1;
    //cin >> t; 
    while(t --) solve();
    
    return 0;
}
```
    - **核心思想**：通过三重循环枚举购买的生命值、攻击力、防御力数量，根据推导的取胜条件判断是否获胜，记录最小花费。

### 最优关键思路或技巧
根据数据范围小的特点，分析出各属性购买量的合理上限进行枚举，从而全面且高效地解决问题。部分题解还利用GCC优化指令加速程序运行。

### 可拓展之处
同类型题通常会给出类似的属性对抗模型，通过改变属性计算方式、获胜条件或资源限制等因素来增加难度。类似算法套路是在数据范围较小时，优先考虑通过枚举所有可能情况来解决问题，同时要善于分析问题找出边界条件，减少不必要的枚举。

### 洛谷推荐题目
- [P1118 数字三角形](https://www.luogu.com.cn/problem/P1118)
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)

### 个人心得摘录与总结
部分作者提到在做题时先思考复杂解法，后发现数据范围允许简单枚举。这表明在面对题目时，既要考虑通用解法，也要留意数据范围等条件，可能存在更简单直接的方法。 

---
处理用时：91.57秒