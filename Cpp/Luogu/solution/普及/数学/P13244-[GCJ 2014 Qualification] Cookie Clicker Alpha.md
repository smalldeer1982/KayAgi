# [GCJ 2014 Qualification] Cookie Clicker Alpha

## 题目背景

Cookie Clicker 是 Orteil 开发的一款 Javascript 游戏，玩家通过点击一个巨大的曲奇图案来获得曲奇。点击巨型曲奇会获得曲奇，可以用这些曲奇购买建筑物，而这些建筑物又会帮助玩家获得更多曲奇。和本题一样，这款游戏非常专注于曲奇。不过本题只是借鉴了类似的思路，不要求你玩过 Cookie Clicker。请现在不要去玩这款游戏：否则你可能很久都回不来。

Cookie Clicker 由 Orteil 创作。Orteil 并未参与 Google Code Jam，也未对其进行背书。

## 题目描述

在本题中，你一开始拥有 $0$ 个曲奇。你以每秒 $2$ 个曲奇的速度获得曲奇，方式是点击巨型曲奇。只要你拥有至少 $C$ 个曲奇，就可以购买一个曲奇农场。每次购买曲奇农场时，你需要花费 $C$ 个曲奇，并且你的曲奇产量每秒提升 $F$ 个曲奇。

一旦你拥有 $X$ 个未用于购买农场的曲奇，你就算获胜！请计算在最优策略下，你需要多长时间才能获胜。

假设 $C = 500.0$，$F = 4.0$，$X = 2000.0$。最优策略如下：

1. 你从 $0$ 个曲奇开始，产量为每秒 $2$ 个曲奇。
2. $250$ 秒后，你将拥有 $C = 500$ 个曲奇，可以购买一个产量为 $F = 4$ 曲奇/秒的农场。
3. 购买农场后，你的曲奇数变为 $0$，总产量变为每秒 $6$ 个曲奇。
4. 下一个农场需要 $500$ 个曲奇，你大约在 $83.3333333$ 秒后可以购买。
5. 购买第二个农场后，你的曲奇数归零，总产量变为每秒 $10$ 个曲奇。
6. 再买一个农场需要 $500$ 个曲奇，你在 $50$ 秒后可以购买。
7. 购买第三个农场后，你的曲奇数归零，总产量变为每秒 $14$ 个曲奇。
8. 再买一个农场仍需 $500$ 曲奇，但其实此时不买更优：直接等待直到拥有 $X = 2000$ 个曲奇，这需要大约 $142.8571429$ 秒。

总耗时：$250 + 83.3333333 + 50 + 142.8571429 = 526.1904762$ 秒。

注意你获得曲奇是连续的：比如游戏开始 $0.1$ 秒后你有 $0.2$ 个曲奇，$\pi$ 秒后你有 $2\pi$ 个曲奇。

## 说明/提示

**数据范围**

- $1 \leq T \leq 100$。

**小数据集（8 分）**

- 时间限制：~~60~~ 3 秒。
- $1 \leq C \leq 500$。
- $1 \leq F \leq 4$。
- $1 \leq X \leq 2000$。

**大数据集（11 分）**

- 时间限制：~~120~~ 5 秒。
- $1 \leq C \leq 10000$。
- $1 \leq F \leq 100$。
- $1 \leq X \leq 100000$。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
4
30.0 1.0 2.0
30.0 2.0 100.0
30.50000 3.14159 1999.19990
500.0 4.0 2000.0```

### 输出

```
Case #1: 1.0000000
Case #2: 39.1666667
Case #3: 63.9680013
Case #4: 526.1904762```

# 题解

## 作者：_DATA_X_ (赞：2)

# P3244 题解：

## 主要思路：

从不买任何农场的情况开始，存储当前情况的时间，然后逐一枚举如果购买一所农场所需要的曲奇的生产时间，如果小于上一个情况，更新当前最优解。

## 代码实现：

定义一个变量 $tz$ 存储答案，初始化为任何农场都不买的情况 $X\div r$，其中 $r$ 定义为当前的生产速度，然后用 while 循环枚举如果购买当前农场所需曲奇的生产时间，如果小于 $tz$，更新 $tz$ 的值。枚举完所有情况后，此时的 $tz$ 存储的就是最优解，输出 $tz$ 的值即可。

**[AC](https://www.luogu.com.cn/record/224648053) Code：**

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int T;
int32_t main(){
	cout.tie(nullptr)->ios::sync_with_stdio(false);
	cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin>>T;
    cout<<fixed<<setprecision(7);//保留七位小数。
    for(int cas=1;cas<=T;cas++){
        double c,f,x;
		cin>>c>>f>>x;
        double e=0.0;
        double r=2.0;
        double tz=x/r; 
        while(1){
            double tx=c/r;
            e+=tx;
            r+=f;
            double ty=e+x/r;
            if(ty<tz) tz=ty;//如果有更优解，更新当前值。
            else break;
        }
        cout<<"Case #"<<cas<<": "<<tz<<endl;//注意输出格式。
    }
}
``````
~求过。~

---

## 作者：Belia (赞：1)

简单的贪心题。

### 思路：

假设我们不买农场，则需要 $\frac{X}{2}$ 个时间单位。

假设我们攒若干个曲奇去买 $k$ 个农场，则需要 $\texttt{累计购买时间} + \texttt{最终等待时间}$ 个时间单位。

很显然，攒曲奇买农场是我们的贪心策略。

由于总时间函数是单峰函数——先减少后增加，所以，最优解就是总时间开始增加时。

代码很好写，一个小模拟就可以搞定。

### 代码：
```cpp
#include<bits/stdc++.h>
#define ll long long//#define ll long long你值得拥有
using namespace std;
ll t;
double c,f,x,ans,sum,tmp,rate;
void solve()
{
    cin>>t;
    for(ll tc=1;tc<=t;tc++)
    {
        cin>>c>>f>>x,ans=x/2.0,sum=0.0,rate=2.0;
        while(1)
        {
            sum+=c/rate,rate+=f,tmp=sum+x/rate;
            if(tmp<ans)
			ans=tmp;
            else
			break;
        }
        printf("Case #%lld: %.7lf\n",tc,ans);
    }
}
int main()
{
    solve();
    return 0;
}
```
$\mathcal{Just}$ $\mathcal{So}$ $\mathcal{So}$!

---

## 作者：hlb44 (赞：1)

这是一道贪心的练习题。

对于这道题目，我们的问题为是否应该购买农场？如果购买农场会消耗当前曲奇，但能提高长期产出效率；不购买则可积累曲奇，但速度较慢。

每次我们有这两种方案：

直接生产：不买农场，用当前速率 $r$ 生产到 $X$ 个曲奇的时间为 $X \div r$。

先买农场再生产：先花时间 $C \div r$ 攒够 $C$ 个曲奇买农场，再以新速率 $r+F$ 生产到 $X$ 个曲奇，总时间为 $C \div r + X \div (r+F)$。

我们比较这两种方案，若方案 1 更优，则停止购买农场，直接生产；否则购买农场并更新速率，重复决策，即可得出答案。

代码：

```cpp
#include<iostream>
#include<iomanip>
using namespace std;
int main() {
	int T;
	cin>>T;
	for(int _=1; _<=T; ++_) {
		double C,F,X;
		cin>>C>>F>>X;
		double t=0,r=2;
		while(1) {
			double d=X/r,b=C/r+X/(r+F);
			if(d<=b) {
				t+=d;
				break;
			}
			t+=C/r;
			r+=F;
		}
		cout<<"Case #"<<_<<": "<<fixed<<setprecision(7)<<t<<endl;
	}
	return 0;
}

```

---

## 作者：Eternally_Moon (赞：1)

# P13244 题解
## 主要思路
首先可以将不买任何一个农场的成功时间储存起来，然后依次枚举出多买一个农场成功所需要的的时间，如果时间小于上一种情况，则继续购买农场，将时间储存起来，否则结束循环，输出最优时间。
## 代码实现
建立变量 $speed$ 储存初始速度，并计算不买任何农场到成功所需要的时间 $ans_i$ 。在重复循环中定义 $buy$ 变量表示当前没买农场前成功所需的时间，定义变量 $sec$ 表示买农场之后成功所需的时间，最后判断如果此时的时间大于上一种情况的时间，那么退出循环，输出最优时间。

#### AC code:
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int t;
double c[N],f[N],x[N],ans[N];//定义
int main(){
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>c[i]>>f[i]>>x[i];
    }//输入
    for(int i=0;i<t;i++){
        double s=0;//每一种情况的时间和
        double speed=2;//饼干生产速度
        ans[i]=x[i]/speed;//初始成功所需的时间
        while(true){
            double buy=c[i]/speed;//买农场前的时间
            s+=buy;
            speed+=f[i];
            double sec=s+x[i]/speed;//买农场后的时间
            if(sec<ans[i])ans[i]=sec;//判断
            else{
                break;//退出
            }
        }
    }
    for(int i=0;i<t;i++){
        cout<<"Case #"<<i+1<<": ";
        printf("%.7lf\n",ans[i]);//保留七位小数
    }
    return 0;//圆满结束
}

```
有错误欢迎指出。

---

## 作者：wangxx2012 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P13244)
## 思路1：模拟
我们只需不断模拟购买一个曲奇农场提高生产速度，再统计时间，找到最小值即可。代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		double C,F,X;
		cin>>C>>F>>X;
		double sum=0.0,cnt=2.0;//sum用来累计用于购买农场的总时间，cnt为当前的曲奇生产速度（初始为2曲奇/秒）
		double ti=X/cnt;//ti用来初始最优时间：不购买任何农场，直接生产X个曲奇的时间
		while(1){//循环购买更多农场
			double time=C/cnt;//计算购买一个新农场需要的时间（当前速度下积累C个曲奇的时间）
			sum+=time;//累加购买农场的时间
			cnt+=F;//购买后，生产速度增加F
			double ans=sum+X/cnt;//计算购买后，积累X个曲奇的总时间（已花费的时间+新速度下生产X个曲奇的时间）
			if(ans<ti) ti=ans;//更新最优
			else break;
		}
		printf("Case #%d: %.7lf\n",i,ti);
	}
	return 0;
}
```
## 思路2：三分
为什么会想到用三分呢？首先我们令总时间函数为 $f(k)$，其中 $k$ 指购买的农场数量。在本题中，当 $k$ 较小时，购买农场能显著提升生产速度，节省后续生产时间，因此总时间 $f(k)$ 随 $k$ 增大而减少。而在 $k$ 足够大时，购买农场需要的时间会超过因速度提升而节省的时间，此时总时间 $f(k)$ 随 $k$ 增大而增加，即总时间函数为 $f(k)$ 为单峰函数，那我们就可用三分来解决这道题。三分代码如下：
```cpp
while(r-l>3){
            //计算两个三等分点
            int m1=l+(r-l)/3;//第一个三等分点
            int m2=r-(r-l)/3;//第二个三等分点
            // 计算两个点的总时间
            double t1=d(m1);
            double t2=d(m2);
            //缩小搜索范围
            if(t1<t2) r=m2;//最优解在左侧，调整右边界
            else l=m1;//最优解在右侧，调整左边界
        }
```
那如何计算两个点的总时间呢？其实和模拟思路相似，代码如下：
```cpp
double d(int n){
	double t=0.0;
	double r=2.0;
	for(int i=1;i<=n;i++){
		t+=C/r;
		r+=F;
	}
	return t+X/r;
}
```
完整代码实现如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
double C,F,X;
double d(int n){
	double t=0.0;
	double r=2.0;
	for(int i=1;i<=n;i++){
		t+=C/r;
		r+=F;
	}
	return t+X/r;
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		cin>>C>>F>>X;
		int l=0,r=1000000;
		while(r-l>3){
			//计算两个三等分点
			int m1=l+(r-l)/3;//第一个三等分点
			int m2=r-(r-l)/3;//第二个三等分点
			// 计算两个点的总时间
			double t1=d(m1);
			double t2=d(m2);
			//缩小搜索范围
			if(t1<t2) r=m2;//最优解在左侧，调整右边界
			else l=m1;//最优解在右侧，调整左边界
		}
		double minn=1e18;
		for(int j=l;j<=r;j++) minn=min(minn,d(j));
		printf("Case #%d: %.7lf\n",i,minn);
	}
	return 0;
}
```

---

## 作者：jsisonx (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P13244)

# 题目分析

首先不难发现，如果要买农场，就要在曲奇数达到 $C$ 的那一刻立即去买，否则假设在 $t$ 时刻曲奇数达到了 $C$，而却在 $t'$ 时刻才买农场，那么 $t$ 到 $t'$ 这段时间里产量本来可以到 $2+F$ 的，而此时产量仍为 $2$，显然不好。

这样，我们唯一要考虑的就是买多少农场，为方便，设 $F_1=2$。

设买了 $k$ 个农场，则买第一个农场需要 $\frac{C}{F_1}$ 秒攒曲奇，买第二个农场需要 $\frac{C}{F_1+F}$ 秒攒曲奇，以此类推，买第 $k$ 个农场需要 $\frac{C}{F_1+(k-1)F}$ 秒攒曲奇。最后获得 $X$ 个曲奇需要 $\frac{X}{F_1+kF}$ 秒。因此，买 $k$ 个农场然后获胜的总耗时为：

$$\operatorname{f}(k)=\sum\limits_{t=1}^{k-1}(\frac{C}{F_1+tF})+\frac{X}{F_1+kF}$$

现在的问题就是求这个函数的最小值。我们注意到，若最小值在 $k=k_0$ 处取得，则 $\operatorname{f}(k_0)\le \operatorname{f}(k_0-1)$ 且 $\operatorname{f}(k_0) \le \operatorname{f}(k_0+1)$。我们又有

$$\begin{aligned} \operatorname{f}(k)-\operatorname{f}(k-1)&=\frac{C}{F_1}+\frac{C}{F_1+F}+\dots +\frac{C}{F_1+(k-1)F}+\frac{X}{F_1+kF}-(\frac{C}{F_1}+\frac{C}{F_1+F}+\dots +\frac{C}{F_1+(k-2)F}+\frac{X}{F_1+(k-1)F}) \\ &= \frac{C}{F_1+(k-1)F}+\frac{X}{F_1+kF}-\frac{X}{F_1+(k-1)F} \end{aligned}$$

同理，$\operatorname{f}(k+1)-\operatorname{f}(k)$ 就应该等于 $\frac{C}{F_1+kF}+\frac{X}{F_1+(k+1)F}-\frac{X}{F_1+kF}$。

因此，问题就变成了解不等式：

$$ \begin{alignedat}{2}
\frac{C}{F_1+(k-1)F}+\frac{X}{F_1+kF}-\frac{X}{F_1+(k-1)F} \le 0 \\
\frac{C}{F_1+kF}+\frac{X}{F_1+(k+1)F}-\frac{X}{F_1+kF} \ge 0
\end{alignedat}$$

上面的不等式解得 

$$ \frac{X}{C}-1-\frac{F_1}{F} \le k \le \frac{X}{C}-\frac{F_1}{F}$$。

由于 $k$ 为整数，所以 $k=\lceil\frac{X}{C}-1-\frac{F_1}{F}\rceil$。

求出 $k$ 以后，带入上述函数求出时间即可。

# 代码


```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	for(int o=1;o<=t;o++){
		cout<<"Case #"<<o<<": ";
		double c,f,x,f1=2.0,ans=0;
		int k;
		cin>>c>>f>>x;
		k=ceil((x-c)/c-(f1/f));
		k=max(0,k);
		for(double i=0;i<=k-1;i+=1){
			ans+=c/(f1+i*f);
		}
		ans+=x/(f1+k*f);
		printf("%.7lf\n",ans);
	}
	return 0;
} 
```

---

## 作者：_aszxqw_ (赞：0)

### 计算总时间：
对于每个 $k$（购买的农场数量），计算购买 $k$ 个农场所需的总时间以及之后直接等待到 $X$ 曲奇的时间。总时间包括：   
1. 购买前 $k$ 个农场的时间：每次购买第 $i$ 个农场需要的时间是 $C\div(2 + F\times(i-1))$。     
1. 购买 $k$ 个农场后，直接等待到 $X$ 曲奇的时间：$X\div(2 + F\times k)$。
### 停止条件：
当增加一个农场后总时间不再减少时停止，此时即为最优解。  
### AC 代码
```
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(0),cin.tie(0);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        double cc, f, x;
        cin >> cc >> f >> x;
        double mt = x / 2.0;  
        double tf = 0.0;
        double c = 2.0;
        for (int k = 1; ; k++) {
            tf += cc / c;
            c += f;
            if (tf + x / c < mt) mt = tf + x / c;
            else break;
        }
        cout << "Case #" << tt << ": " << fixed << setprecision(7) << mt << '\n';
    }
    return 0;
}
```

---

