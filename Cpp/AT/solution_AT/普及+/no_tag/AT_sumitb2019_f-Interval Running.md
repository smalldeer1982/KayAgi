# Interval Running

## 题目描述

[problemUrl]: https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_f

高橋君と青木君は、西から東に向けて一直線に果てしなく続くランニングコースで長距離走の練習をしています。

彼らは同じ地点から同時にスタートし、**東に向かって**次のように移動します。

- 高橋君は最初の $ T_1 $ 分間、分速 $ A_1 $ メートルで走り、次の $ T_2 $ 分間、分速 $ A_2 $ メートルで走り、これを交互にいつまでも繰り返す。
- 青木君は最初の $ T_1 $ 分間、分速 $ B_1 $ メートルで走り、次の $ T_2 $ 分間、分速 $ B_2 $ メートルで走り、これを交互にいつまでも繰り返す。

さて、高橋君と青木君は何回出会う、すなわち、同じ位置に来るでしょうか？スタート地点にいる時は数えません。無限回出会う場合は、その旨を報告してください。

## 说明/提示

### 制約

- $ 1\ \leq\ T_i\ \leq\ 100000 $
- $ 1\ \leq\ A_i\ \leq\ 10^{10} $
- $ 1\ \leq\ B_i\ \leq\ 10^{10} $
- $ A_1\ \neq\ B_1 $
- $ A_2\ \neq\ B_2 $
- 入力中の値はすべて整数

### Sample Explanation 1

彼らはスタートしてから $ \frac{4}{3} $ 分後に $ 1 $ 回だけ、スタート地点から $ \frac{40}{3} $ メートルの位置で出会います。

### Sample Explanation 2

彼らはスタートしてから $ 101,\ 202,\ 303,\ 404,\ 505,\ 606,\ ... $ 分後に出会うので、無限回出会うことになります。

### Sample Explanation 3

入力中の値は $ 32 $ ビット整数型に収まらないことがあります。

## 样例 #1

### 输入

```
1 2
10 10
12 4```

### 输出

```
1```

## 样例 #2

### 输入

```
100 1
101 101
102 1```

### 输出

```
infinity```

## 样例 #3

### 输入

```
12000 15700
3390000000 3810000000
5550000000 2130000000```

### 输出

```
113```

# 题解

## 作者：ICE__LX (赞：4)

由公式 $v=\frac{s}{t}$ 可得 $s=vt$，现已知两个物体分两段运动，第一段两个物体运动的速度分别为 $a_1$ 与 $b_1$ 以及运动时间 $t_1$，第二段两个物体运动的速度分别 $a_2$ 与 $b_2$ 以及运动时间 $t_2$。  
由此可得两段运动中两个物体的距离之差 $s_1=(a_1-b_1)\times t_1$ 与 $s_2=(a_2-b_2)\times t_2$。   

然后我们进行分类讨论：  

1. 第一种情况：$s_1+s_2=0$  
距离差为 $0$ 代表两个物体相遇，而两段运动的距离差之和为 $0$ 代表两段运动后这两个物体就刚好相遇，这就代表每进行两段运动就会相遇一次，也就一直可以相遇。  

2. 第二种情况：$s_1$ 与 $s_2$ 都小于或大于 $0$   
出现这种情况代表两个物体在两段运动中的距离一直处于增加的状态，因此它们永远不可能相遇。

3. 第三种情况：$s_1<s_2$ 时 $|s_1|>s_2$ 或 $s_1>s_2$ 时 $|s_1|>-s_2$  
物体一比物体二的速度永远快或慢，因此两个物体在两段运动中的距离也就一直处于非减少的状态，这种情况带来的后果和情况二相同，两个物体永远不可能相遇。

4. 第四种情况：不满足以上情况的所有情况  
以第一次的第一段运动为基础，初始距离为 $s$，以后的距离每相遇一次就会缩小 $s_1-s_2$，当 $s$ 缩小至小于等于 $0$ 时，当前状况就变成了情况三或情况二了，就不会在出现相遇的情况了。因此很容易计算出其相遇的总次数为 $\lfloor \frac{s_1}{s_1-s_2} \rfloor+1$。 注意当 $s_1 \bmod (s_1-s_2) =0$ 时代表 $s$ 最终会变为 $0$，因此这种情况相的相遇次数会比一般情况下少一，相遇次数为  $\lfloor \frac{s_1}{s_1-s_2} \rfloor$。  

由以上结论最终可得出一段极其简短的核心代码。  

```cpp
if(s1+s2==0) puts("infinity");//情况一 
else if((s1<0&&s2<0)||(s1>0&&s2>0)||(abs(s1)>(s1<0?s2:-s2))) puts("0");//情况二和三 
else write(abs(s1)%abs(s1+s2)==0?abs(s1)/abs(s1+s2)*2:abs(s1)/abs(s1+s2)*2+1);//情况四 
```
### 全代码  

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define deap(i,a,b) for(int i=a;i>=b;i--)
const int maxn=INT_MAX;
const double INF=DBL_MAX;
inline int read() {
	int x=0,f=1;
	char ch=getchar();
	while (ch<'0'||ch>'9') {
		if (ch=='-') f=-1;
		ch=getchar();
	}
	while (ch>='0'&&ch<='9') {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*f;
}
inline void write(int x){
	if(x>9)write(x/10);
	putchar(x%10+'0');
}
signed main() {
	int t1=read(),t2=read(),a1=read(),a2=read(),b1=read(),b2=read();
    int s1=(a1-b1)*t1;  
	int s2=(a2-b2)*t2;
    if(s1+s2==0) puts("infinity");//情况一 
	else if((s1<0&&s2<0)||(s1>0&&s2>0)||abs(s1)>(s1<0?s2:-s2)) puts("0");//情况二和三 
    else write(abs(s1)%abs(s1+s2)==0?abs(s1)/abs(s1+s2)*2:abs(s1)/abs(s1+s2)*2+1);//情况四 
	return 0;
}
```

---

## 作者：ZH_qaq (赞：1)

## AT5643 Interval Running的题解
#### [洛谷传送门](https://www.luogu.com.cn/problem/AT5643)
#### [AT传送门](https://atcoder.jp/contests/sumitrust2019/tasks/sumitb2019_f)
### 题目大意
有甲、乙两人在一条无限长度的跑道上跑步，在开始 $T_1$ 分钟内甲的速度为 $A_1$，乙的速度为 $B_1$，再之后 $T_2$ 分钟内甲、乙的速度分别为 $A_2$、$B_2$，再之后 $T_1$ 分钟内甲、乙的速度分别为 $A_1$、$B_1$ $\cdots$ 如此交替往复。问甲乙两人有多少次相遇，若一直可以相遇则输出 infinity。
### 思路
先输入 $T_1$，$T_2$，$A_1$，$A_1$，$B_1$，$B_2$。然后计算在 $T1$ 秒时，甲乙的距离，在 $T2$ 秒时，甲乙的距离。然后再判断相遇。
### 代码
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    ll t1, t2, a1, a2, b1, b2;
    cin >> t1 >> t2 >> a1 >> a2 >> b1 >> b2;
    ll x = (a1 - b1) * t1; // 在T1秒时，甲乙的距离。 
	ll y = (a2 - b2) * t2; // 在T2秒时，甲乙的距离。
    if (x + y == 0) {
        cout << "infinity" << endl; // 相加为0，就说明两人一直相遇。 
        return 0;
    }
    if ((x > 0 && x + y > 0) || (x < 0 && x + y < 0)) {
        cout << "0" << endl; // 如果两人第一次，第二次距离越来越远。就输入0 
        return 0;
    }
    ll df = abs(x + y);
    ll d1 = abs(x);
    ll c = (d1 / df) * 2;
    if (d1 % df != 0) c++; // 判断是否相遇 
    cout << c << endl;
    return 0;
}
```

---

## 作者：ny_123457 (赞：0)

### Part 1.思路
就是一个简单的追及问题，可以先看 $T_1$ 和 $T_2$ 是甲和乙的距离，当然，这个距离是甲的坐标位置减去乙的，如果这两个距离加起来为 $0$ 就会一直相遇。

如果这两个同号切差距越来越大就永远不会相遇，输出 `infinity`。

后面直接当普通的追及问题计算即可（数据较大记得开 `long long`）。

### Part 2.代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t1,t2,a1,a2,b1,b2,l,r,distb,dista,ans;
int Ceil(int a,int b){
	int cnt=0;
	if(a%b!=0)cnt++;
	cnt+=a/b*2;
	return cnt;
}
signed main(){
	cin>>t1>>t2>>a1>>a2>>b1>>b2;
	l=(a1-b1)*t1;
	r=(a2-b2)*t2;
	if(l+r==0)cout<<"infinity";
	else if((l>0&&l+r>0)||(l<0&&l+r<0))cout<<"0";
	else{
		distb=abs(l+r);
		dista=abs(l);
		ans+=Ceil(dista,distb);
		cout<<ans;
	}
	return 0;
}
```

---

## 作者：cosf (赞：0)

## [SumitB2019F](https://www.luogu.com.cn/problem/AT_sumitb2019_f)

首先，时间和具体位置是没什么用的。

我们可以只计算相对位置。以下令相对速度 $v_1 = a_1 - b_1, v_2 = a_2 - b_2$，以及相对距离 $s_1 = t_1v_1, s_2 = -t_2v_2$。

如果 $v_1$ 和 $v_2$ 同号，显然两人的距离会越来越远，不会再相遇。

否则 $s_1$ 和 $(-s_2)$ 一定异号。因为数据正负对称，所以我们可以假设 $s_1$ 为正，$(-s_2)$ 为负。

至此，我们可以把他们两人运动的过程抽象成一个点，从原点开始匀速往右移动 $s_1$ 距离，然后往左移动 $s_2$ 距离，如此反复。

如果 $s_1 > s_2$，显然他们不会再相遇了，因为第 $i$ 个“极小值”是 $i(s_1 - s_2)$，这个会是正的。

如果 $s_1 = s_2$，则他们会无穷无尽地相遇。因为这样他们的平均速度就是 $0$。

如果 $s_1 < s_2$，则会有有限次相遇。

先放出最终的式子：

$$
\text{Answer} = \begin{cases}
2\lfloor\frac{s_1}{s_2 - s_1}\rfloor & (s_2 - s_1) \not| s_1\\
\frac{2s_1}{s_2 - s_1} + 1 & (s_2 - s_1) | s_1
\end{cases}
$$

我们可以这样理解。

他们的距离差先达到了极大值 $s_1$，然后定义“一个周期”为向左移动 $s_2$ 再向右移动 $s_1$，显然一个周期结束后位置会往左一点。而每一个周期，他们的距离差显然会经过两次零点，周期的个数是 $\lfloor\frac{s_1}{s_2 - s_1}\rfloor$。而当这个分数本身就是整数时，某一次周期结束在零点，而这次不会被算在这个式子当中，所以最终要加上 $1$。

## 代码

```cpp
#include <iostream>
using namespace std;

using ll = long long;

int main()
{
    ll t1, t2;
    ll a1, a2, b1, b2;
    cin >> t1 >> t2 >> a1 >> a2 >> b1 >> b2;
    a1 -= b1;
    a2 -= b2;
    a1 *= t1;
    a2 *= t2;
    if (a1 > 0 && a2 > 0)
    {
        cout << 0 << endl;
        return 0;
    }
    if (a1 < 0 && a2 < 0)
    {
        cout << 0 << endl;
        return 0;
    }
    if (a1 < 0)
    {
        a1 = -a1;
        a2 = -a2;
    }
    a2 = -a2;
    if (a1  == a2)
    {
        cout <<  "infinity" << endl;
        return 0;
    }
    if (a1 > a2)
    {
        cout << 0 << endl;
        return 0;
    }
    ll dif = a2 - a1;
    ll lgs = a1;
    if (lgs % dif)
    {
        cout << 2 * (lgs / dif) + 1 << endl;
    }
    else
    {
        cout << 2 * (lgs / dif) << endl;
    }
    return 0;
}
```

---

## 作者：chl090410 (赞：0)

## The Solution to AT_sumitb2019_f Interval Running

### 题目大意

有甲、乙两人在一条无限长度的跑道上跑步，在开始 $T_1$ 分钟内甲的速度为 $A_1$，乙的速度为 $B_1$，再之后 $T_2$ 分钟内甲、乙的速度分别为 $A_2$、$B_2$，再之后 $T_1$ 分钟内甲、乙的速度分别为 $A_1$、$B_1$……如此交替往复。

问甲乙两人有多少次相遇，若一直可以相遇则输出 ```infinity```。

### Solution

我们假设甲快乙慢（若实际与假设相反，因为只求相遇次数，不求两人途中的顺序，所以可以交换甲乙的运动情况。）

为了方便表示，我们设开始的 $T_1$ 分钟与后来的的 $T_2$ 分钟总共为一个周期，一个周期中甲走了 $S_a$，乙走了 $S_b$。而开始的 $T_1$ 分钟甲走了 $S_{a1}$，乙走了 $S_{b1}$，后来的的 $T_2$ 分钟甲走了 $S_{a2}$，乙走了 $S_{b2}$。

若 $S_a=S_b$，则甲乙在每个周期末都会相遇，而周期有无数个，所以甲乙就会相遇无数次。此时输出 ```infinity```。

若 $S_{a1}>S_{b1}$，因为甲比乙快，所以 $S_a>S_b$，而乙的速度不会变，所以乙不可能在后来的的 $T_2$ 分钟内把甲超过又被甲反超。所以此时甲乙永远不会相遇，此时输出 $0$。

若 $S_{a1}<S_{b1}$，因为甲比乙快，所以 $S_a>S_b$，此时甲乙的运动情况大致如下：乙先比甲快，然后被甲超过，一段时间后甲又被乙超过，再一段时间后乙又被甲超过……如此交替往复。

设 $S_a-S_b=l$，$S_{a1}-S_{b1}=u$。每一个周期甲都会被乙多走 $l$，$n$ 个周期后甲就比乙多走了 $nl$，当 $nl>u$ 时，乙就不再追得上甲了。所以甲乙会相遇的周期数（第一周期除外）为 $\dfrac{u}{l}$，因为每个周期（第一周期除外）都是乙先追上甲，又被甲反超，一共相遇两次，所以总相遇次数就为 $\dfrac{u}{l}\times2$ 加上第一周期的 $1$ 次，总共 $\dfrac{u}{l}\times2+1$ 次。

但当 $u$ 能被 $l$ 整除时，最后一次相遇时乙只是追上了甲，并未超过甲，所以这一周期不存在甲反超乙的那一次相遇，相遇数就只有一次。此时总相遇次数为 $\dfrac{u}{l}\times2+1-1=\dfrac{u}{l}\times2$ 次。

### Accode 如下：

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t1,t2,a1,a2,b1,b2,x,y,z,a,b,c,lcr;
signed main(){
	cin>>t1>>t2>>a1>>a2>>b1>>b2;
	x=a1*t1;y=a2*t2;z=b1*t1;a=b2*t2;
	if(x+y==a+z){
		cout<<"infinity";
		return 0;
	}else{
		if((x>z&&y>a)||(x<z&&y<a)){
			cout<<0;
			return 0;
		}
		b=x+y;c=z+a;
		if((b>c&&x>z)||(b<c&&x<z)){
			cout<<0;
			return 0;
		}
		if(b>c){
			int p=b-c;
			int u=z-x;
			if(u%p!=0){
				lcr=1;
			} 
			cout<<u/p*2+lcr;
		}else{
			int p=c-b;
			int u=x-z;
			if(u%p!=0){
				lcr=1;
			} 
			cout<<u/p*2+lcr;
		}
	}
	return 0;
}

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

A 和 B 正在赛跑，前 $T_1$ 分钟 A 和 B 速度分别是 $A_1$ 和 $A_2$，之后 $T_2$ 分钟 A 和 B 速度分别是 $A_2$ 和 $B_2$，以此类推，问 A 和 B 会相遇几次。

相遇无数次输出 `infinity`。

# 题目思路

什么小学奥数入门题。

为了方便描述：

前半段：$S_{a,1}=T_1\times A_1,S_{b,1}=T_1\times B_1$。

后半段：$S_{a,2}=T_2\times A_2,S_{b,2}=T_2\times B_2$。

全程：$S_a=S_{a,1}+S_{a,2},S_b=S_{b,1}+S_{b,2}$。

首先考虑无数次，显然的，A 一个全程与 B 一个全程路程相同即可，即 $S_a=S_b$。

然后我们为了方便描述，强制转换一下，因为本题不用关心前后半程相对顺序与两个人的相对顺序，令 $S_a>S_b$，之后方便我们的描述。

此时如果 $S_{b,1}\lt S_{a,1}$，那么就不会产生任何相遇，直接特判掉。

然后再次令 $S_{a,1}\lt S_{b,1},S_{a,2}\gt S_{b,2}$。即让 A 前半程跑不过 B，但是后半程能追上。

此时就变成了一般情况，A 每个全程比 B 多跑的要去一直填补被 B 甩下的距离，因此所有全程的相遇次数就是 $\left\lfloor\dfrac{S_{b,1}-S_{a,1}}{S_a-S_b}\right\rfloor\times2$。

然后注意一个细节就是可能半程就把最后一次相遇追上了，所以最后要加上 $[(S_{b,1}-S_{a,1})\bmod (S_a-S_b)\neq 0]$。

# 丑陋代码

[AT submission 46471947](https://atcoder.jp/contests/sumitrust2019/submissions/46471947)

---

