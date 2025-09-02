# [GCJ 2022 Qualification] 3D Printing

## 题目描述

你是数据库设计日庆祝活动的组委会成员之一，负责宣传工作，并计划打印三个 **D** 字来设计比赛标志。你可以选择任何颜色打印它们，但所有三个 **D** 必须使用相同的颜色。

![](https://cdn.luogu.com.cn/upload/image_hosting/n2ye797y.png)

你拿到了三台打印机，每台将用于打印其中一个 **D**。所有打印机都使用 4 种不同颜色（青色、品红色、黄色和黑色）的独立墨盒来调配颜色。对于这些打印机，一种颜色由 4 个非负整数 $c$、$m$、$y$ 和 $k$ 唯一确定，分别表示调配该颜色所需的青色、品红色、黄色和黑色墨水的单位数。

打印单个 **D** 所需的墨水总量恰好是 $10^6$ 单位。例如，纯黄色打印一个 **D** 需要 $10^6$ 单位黄色墨水，其余颜色为 $0$；而用 Code Jam 红色打印则需要 $0$ 单位青色墨水、$500000$ 单位品红色墨水、$450000$ 单位黄色墨水和 $50000$ 单位黑色墨水。

要打印某种颜色，打印机必须在每个颜色的墨盒中至少有该颜色所需的墨水单位数。给定每台打印机各墨盒中的墨水单位数，输出任意一种满足以下条件的颜色（定义为 4 个非负整数，其和为 $10^6$）：所有三台打印机均有足够墨水打印该颜色。


## 说明/提示


## 说明/提示

**样例解释**

样例 #1 对应题目描述中的图片。给出的颜色方案用尽了第一台打印机的青色、品红色和黄色墨盒的所有墨水，以及最后一台打印机的黑色墨盒的所有墨水。这意味着无法再从任何颜色的墨盒中多用一单位墨水，因此该样例输出是此案例唯一可能的解。

在样例 #2 中，品红色是前两台打印机唯一共有的颜色，因此唯一可能的方案是使用 $10^6$ 单位品红色墨水。但第三台打印机的品红色墨水不足，导致此案例无解。

在样例 #3 中，其他正确输出包括 `"400000 100000 100000 400000"`、`"300000 0 0 700000"` 和 `"350000 140000 160000 350000"` 等。注意 `"300000 140000 160000 700000"` 不是有效答案，因为尽管所有打印机均有足够墨水，但墨水单位总数必须严格等于 $10^6$。

**限制条件**

**测试集 1（可见评测结果）**

- $1 \leq \mathbf{T} \leq 100$。
- $0 \leq \mathbf{C}_i \leq 10^6$，对所有 $i$ 成立。
- $0 \leq \mathbf{M}_i \leq 10^6$，对所有 $i$ 成立。
- $0 \leq \mathbf{Y}_i \leq 10^6$，对所有 $i$ 成立。
- $0 \leq \mathbf{K}_i \leq 10^6$，对所有 $i$ 成立。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
3
300000 200000 300000 500000
300000 200000 500000 300000
300000 500000 300000 200000
1000000 1000000 0 0
0 1000000 1000000 1000000
999999 999999 999999 999999
768763 148041 178147 984173
699508 515362 534729 714381
949704 625054 946212 951187```

### 输出

```
Case #1: 300000 200000 300000 200000
Case #2: IMPOSSIBLE
Case #3: 400001 100002 100003 399994```

# 题解

## 作者：xcy_duaiyita (赞：3)

# [题目传送门](https://www.luogu.com.cn/problem/P12980)
水题水题水题！！！

## 题目大意    
给你一个 $3\times 4$ 的数列，让你找 $4$ 个数，要求：   

1.这 $4$ 个数满足：第 $i$ 个数**小于或等于第 $i$ 列上所有的数** $(1\le i\le 4)$。    
2.这 $4$ 个数相加**必须等于 $10^6$**。

## 题目思路
~~看似数学，实则贪心。~~   

但如何去贪心呢？   
我们拿一个数组 $ans$ 去记我们找的 $4$ 个数，用变量 $sum$ 去记录我们选的数的和。首先可以证明，**我们从每列的 $3$ 个数中选择最小数一定是最优的**。我们可以先从左往右遍历每列，找出第 $i$ 列的最小值 $min_i$，接着我们去判断：如果 $sum+min_i<10^6$，说明不够，还得加，就将 $min_i$ 存入 $ans_i$，并且将 $sum$ 加上 $min_i$；如果 $sum+min_i\ge 10^6$，则说明到这里就够了，就将 $10^6-sum$ 存入 $ans_i$，并且给 $sum$ 赋值为 $10^6$，然后 break 掉就行。

最后，我们判断一下 $sum$ 的值：若 $sum=10^6$，则输出数组 $ans$；反之输出 `IMPOSSIBLE`。    
**输出时一定要注意格式！！！注意空格数量和大小写！！！**

## 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int G=1e6;
int T,a[8][8],ans[8],sum;
void solve(int x){
	memset(ans,0,sizeof(ans));
    //初始化ans，这样有个好处就是后续可以直接输出0
	sum=0;
	for(int i=1;i<=3;i++){
		for(int j=1;j<=4;j++){
			cin>>a[i][j];
		}
	}
   //读入
	for(int j=1;j<=4;j++){
		int mn=1e7;
		for(int i=1;i<=3;i++) mn=min(a[i][j],mn);
    //求这一列的最小值
		if(sum+mn>=G){//判断够没够
			ans[j]=G-sum,sum=G;
			break;
		}else ans[j]=mn,sum+=mn;
	}cout<<"Case #"<<x<<":";
	if(sum==G){
		for(int i=1;i<=4;i++) cout<<" "<<ans[i];
		cout<<endl;
	}else cout<<" IMPOSSIBLE"<<endl;//这里一定要记得空格！！！
    //输出
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>T;
	for(int i=1;i<=T;i++) solve(i);
}
```
时间复杂度：$O(24)$。
#### 完美AC！！！    
#### [评测记录。](https://www.luogu.com.cn/record/229228579)

QwQ管理员大大求过！！！

---

## 作者：Ghosty_Neutrino (赞：2)

## 题意
本题要求为三台打印机选择一个共同颜色，使得该颜色的青（$C$）、品红（$M$）、黄（$Y$）、黑（$K$）墨量满足：
* 每个墨量不超过任意一台打印机对应墨盒的可用量。
* 四个墨量之和恰好为 $1000000$ 单位。
* 若存在这样的颜色，输出任意一组解；否则输出 `IMPOSSIBLE`。
## 分析
对每个颜色分量（$C$，$M$，$Y$，$K$），取三台打印机对应墨量的最小值，得到候选值。

若四个候选值之和小于 $1000000$，则无解。

若和大于等于 $1000000$，通过调整候选值使总和恰好为 $1000000$。
## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int TARGET=1000000;
int t,p1[4],p2[4],p3[4];
main(){
	scanf("%d",&t);
	for(int i=1;i<=t;i++){
        //读取三台打印机的墨量
		for(int j=0;j<4;j++) scanf("%d",&p1[j]);
		for(int j=0;j<4;j++) scanf("%d",&p2[j]);
		for(int j=0;j<4;j++) scanf("%d",&p3[j]);
		//计算各颜色分量的最小值
		int minc=min({p1[0],p2[0],p3[0]});
		int minm=min({p1[1],p2[1],p3[1]});
		int miny=min({p1[2],p2[2],p3[2]});
		int mink=min({p1[3],p2[3],p3[3]});
		//计算最小值之和
		int t=minc+minm+miny+mink;
		if(t<TARGET){
			printf("Case #%d: IMPOSSIBLE\n",i);
			continue;
		}
        //调整分量使总和为1,000,000
        int del=t-TARGET;
        int c[4]={minc,minm,miny,mink};
        //从后往前调整（K→Y→M→C）
        for(int j=3;j>=0&&del>0;j--){
            int sub=min(del,c[j]);
            c[j]-=sub;
            del-=sub;
        }
        //输出结果，大功告成
        printf("Case #%d: %d %d %d %d\n",i,c[0],c[1],c[2],c[3]);		        
	}
	return 0;
}
```

---

## 作者：zhongjunnan561234 (赞：1)

# 题意
给定 $n$ 组数据，每组包含 $12$ 个数字。现在需要判断：第 $1$ 列的最小值、第 $2$ 列的最小值、第 $3$ 列的最小值和第 $4$ 列的最小值之和是否不超过 $10^6$。
# 思路
**计算每列的最小值**：对于每一列，找到该列中的最小数值，记为 $g1$，$g2$，$g3$，$g4$。

**求和并判断**：

- 计算 $S=g1+g2+g3+g4$。

- 如果 $S≥10^{6}$ ：

   - 按顺序输出 $g1$，$g2$，$g3$，$g4$ ，但需确保它们的总和正好是 $10^{6}$ ：
   - 调整方法：从 $g1$ 开始，尽可能多地取，剩余部分由后续 $gi$ 补足。
- 如果$S<10^{6}$ ：

  - 直接输出 `IMPOSSIBLE`。
# AC Code
```
#include<bits/stdc++.h>
using namespace std;
void prin(long long a,long long b,long long c,long long d){
    long long s=1000000;
    if(s<=a)cout<<s,s=0;
    else cout<<a,s-=a;
    cout<<" ";
    if(s<=b)cout<<s,s=0;
    else cout<<b,s-=b;
    cout<<" ";
    if(s<=c)cout<<s,s=0;
    else cout<<c,s-=c;
    cout<<" ";
    if(s<=d)cout<<s,s=0;
    else cout<<d,s-=d;
    cout<<" ";
}//输出
int min_(long long x,long long y,long long z){
    return min(min(x,y),z);
}//每一列的最小值
int main(){
    int n;
    long long a,b,c,d,e,f,g,h,i,j,k,l,m1,m2,m3,m4;
    cin>>n;
    for(int p=1;p<=n;p++){
        cin>>a>>b>>c>>d>>e>>f>>g>>h>>i>>j>>k>>l;
        m1=min_(a,e,i),m2=min_(b,f,j),m3=min_(c,g,k),m4=min_(d,h,l);
        cout<<"Case #"<<p<<": ";
        if((m1+m2+m3+m4)>=1000000)prin(m1,m2,m3,m4);
        else cout<<"IMPOSSIBLE";//无法凑数，输出"IMPOSSIBLE"
        cout<<endl;
    }
}
`

---

## 作者：tujiaqi12 (赞：1)

## 思路
因为每一个答案要低于所有打印机能提供的最低值，所以不妨把每一个颜色最多能使用的量结合起来。也就是下面的表格。

|c|m|y|k|
|:-:|:-:|:-:|:-:|
 | $\min(c1,c2,c3,10^6)$ | $\min(m1,m2,m3,10^6)$ | $\min(y1,y2,y3,10^6)$ | $\min(k1,k2,k3,10^6)$ | 

我们只要判断**颜色总量**，也就是下面的公式。

$\min(c1,c2,c3,10^6) + \min(m1,m2,m3,10^6) + \min(y1,y2,y3,10^6) + \min(k1,k2,k3,10^6)$

是否能达到 $10^6$，即可判断是否能成功打印，接下来的步骤相信你一定知道可以怎么做了。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll t;
ll mi[4];//最少颜色 
int main(){
	scanf("%lld",&t);
	for(ll i = 1;i <= t;i++){
		ll x;
		for(ll j = 0;j <= 3;j++){
			mi[j] = 1000000;
		}
		for(ll j = 1;j <= 3;j++){
			for(ll k = 0;k <= 3;k++){
				scanf("%lld",&x);
				mi[k] = min(mi[k],x);//最少颜色 
			}
		}
		printf("Case #%lld: ",i);
		if(mi[0]+mi[1]+mi[2]+mi[3] >= 1e6){
			ll sh = 1e6;
			for(ll j = 0;j <= 3;j++){
				ll ans = min(sh,mi[j]);//防止总量超出1e6 
				printf("%lld ",ans);
				sh -= ans;
			}
		}
		else{
			printf("IMPOSSIBLE");
		}
		printf("\n");
	}
	return 0;
}
```

---

## 作者：wjh27465 (赞：0)

# 题解：P12980 [GCJ 2022 Qualification] 3D Printing
## 分析
此题读入数据后，先取三台打印机青色、品红色、黄色、黑色墨水量的最小值，分别记为 $r1,r2,r3,r4$，表示打印机能打印出的最大墨水量。之后将 $r1,r2,r3,r4$ 加和，若小于 $10^6$ 则说明无法做到，输出`IMPOSSIBLE`。  
若 $r1,r2,r3,r4$ 的和大于等于 $10^6$，就把 $r4$ 更改为 $10^6-r1-r2-r3$，保证和严格等于 $10^6$。如果 $r4<0$，那么再调整 $r1,r2,r3$ 的值。最后输出 $r1,r2,r3,r4$ 即可。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        int c1,m1,y1,k1,c2,m2,y2,k2,c3,m3,y3,k3,r1,r2,r3,r4;
        cin>>c1>>m1>>y1>>k1>>c2>>m2>>y2>>k2>>c3>>m3>>y3>>k3;
        r1=min(min(c1,c2),c3);
        r2=min(min(m1,m2),m3);
        r3=min(min(y1,y2),y3);
        r4=min(min(k1,k2),k3);
        if(r1+r2+r3+r4<1000000)
            cout<<"Case #"<<i<<": IMPOSSIBLE"<<endl;
        else
        {
            r4=1000000-r1-r2-r3;
            if(r4<0)
            {
                r3+=r4;
                r4=0;
                if(r3<0)
                {
                    r2+=r3;
                    r3=0;
                    if(r2<0)
                    {
                        r1+=r2;
                        r2=0;
                    }
                }
            }
            cout<<"Case #"<<i<<": "<<r1<<" "<<r2<<" "<<r3<<" "<<r4<<endl;
        }
    }
    return 0;
}
```

---

## 作者：Noob_Oler (赞：0)

# 题解：P12980 [GCJ 2022 Qualification] 3D Printing

直接模拟，找出 $c$，$m$，$y$，$k$，$4$ 个数组中的 $3$ 个打印机中的最小值。

之后，如果这 $4$ 个值的和 $\ge 10^6$ 就可以输出。

但是要保证这四个值的和要等与 $10^6$，那么我们就需要一个变量 $s$ 他的初值是 $10^6$。

之后在一个一个减去 $\min(s,a)$（$a$ 数组存的是每个颜色中的最小值）

# Code

```
#include <bits/stdc++.h>
using namespace std;
int c[5],m[5],y[5],k[5],a[5];
int main()
{
    int t;
    cin >> t;
    int sdkwf = 0;
    while(t--)
    {
        sdkwf++;
        for(int i = 1; i <= 3; i++) cin >> c[i] >> m[i] >> y[i] >> k[i];
        int mc = 1e9,mm = 1e9,my = 1e9,mk = 1e9;
        for(int i = 1; i <= 3; i++)
        {
            mc = min(mc,c[i]);
            mm = min(mm,m[i]);
            my = min(my,y[i]);
            mk = min(mk,k[i]);
        }
        if(mc + mm + my + mk >= 1e6)
        {
            a[1] = mc;
            a[2] = mm;
            a[3] = my;
            a[4] = mk;
            cout << "Case #" << sdkwf << ": ";
            int s = 1e6;
            for(int i = 1; i <= 4; i++)
            {
                int x = min(s,a[i]);
                cout << x << " ";
                s -= x;
            }
            cout << "\n";
        }
        else cout << "Case #" << sdkwf << ": IMPOSSIBLE\n";
    }
    return 0;
}
```

---

## 作者：Hkb150429 (赞：0)

审核求过 QAQ！

[题目传送门](https://www.luogu.com.cn/problem/P12980)

## 题意
给定 $n$ 组数，每组 $12$ 个数，现在求第 1 列的最小值加第 2 列的最小值加第 3 列的最小值加第 4 列的最小值大不大于 $10^{6}$。

## 思路

求出每列的最小值 $g1$，$g2$，$g3$，$g4$，在把他们加起来，如果和大于等于 $10^{6}$，按顺序输出它们并且使它们的和等于 $10^{6}$，否则输出  `IMPOSSIBLE`。

## AC CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int mi(long long a,long long b,long long c){
    return min(min(a,b),c);
}//求每一列的最小值
void prin(long long a,long long b,long long c,long long d){
    long long t=1000000;
    if(t>a)cout<<a,t-=a;
    else cout<<t,t=0;
    cout<<' ';
    if(t>b)cout<<b,t-=b;
    else cout<<t,t=0;
    cout<<' ';
    if(t>c)cout<<c,t-=c;
    else cout<<t,t=0;
    cout<<' ';
    if(t>d)cout<<d,t-=d;
    else cout<<t,t=0;
    cout<<' ';
}//按顺序输出
int main(){
    int n;
    long long a,b,c,d,e,f,g,h,i,j,k,l,g1,g2,g3,g4;
    cin>>n;
    for(int p=1;p<=n;p++){
        cout<<"Case #"<<p<<": ";
        cin>>a>>b>>c>>d>>e>>f>>g>>h>>i>>j>>k>>l;
        g1=mi(a,e,i),g2=mi(b,f,j),g3=mi(c,g,k),g4=mi(d,h,l);
        if((g1+g2+g3+g4)<1000000)cout<<"IMPOSSIBLE";//如果无法凑数，输出"IMPOSSIBLE"
        else prin(g1,g2,g3,g4);
        cout<<endl;
    }
}
```

---

## 作者：PDcccc_M (赞：0)

## 题意

我们需要找到四个非负整数 $c,m,y,k$ 满足：

1. $c+m+y+k=10^6$
2. $c≤C_i$
3. $m≤M_i$
4. $k≤K_i$
5. $y≤Y_i$

## 思路

对每种颜色，取三台打印机的最小存量，这样保证单个颜色的可用量最大且不会超过打印机存量。即：

$c_{max} = \min(C_1,C_2,C_3)$

$m_{max} = \min(M_1,M_2,M_3)$

$k_{max} = \min(K_1,K_2,K_3)$

$y_{max} = \min(Y_1,Y_2,Y_3)$

显然，如果可用总量小于 $10^6$ 则无解。

如果有解的构造方法如下：

1. 初始化剩余量为 $10^6$。
2. 对每种颜色分配，即：
   $$当前颜色取值=\min(该颜色可用量,当前剩余量)$$
3. 更新剩余量。
4. 当剩余量为 $0$ 时，构造结束，输出即可。

## 代码

```cpp
#include <iostream>
#include <algorithm>
#define MAX 0x7fffffffffffffff
using namespace std;
int main()
{
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        long long p[3][4], m[4] = {MAX, MAX, MAX, MAX}, s = 0, r = 1e6, c[4];
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                cin >> p[i][j];
        for (int j = 0; j < 4; j++)
        {
            for (int i = 0; i < 3; i++)
                m[j] = min(m[j], p[i][j]);
            s += m[j];
        }
        cout << "Case #" << t << ": ";
        if (s < 1e6)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        for (int i = 0; i < 4; i++)
            c[i] = min(m[i], r), r -= c[i];
        cout << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << "\n";
    }
}
```

时间复杂度 $O(T)$。

---

## 作者：皓月星辉 (赞：0)

## PART1 简化题意
本题有多组数据，对于每次询问，给定 $3$ 个四元组，要求输出一个四元组满足该四元组四个元素和为 $10^6$ 并且每个元素都不大于给定的三个四元组的对应元素。
## PART2 分析
典型贪心策略，对四个元素依次处理，尽可能取最大量，即取三个四元组对应位置的最小元素。

若每个位置都取了最大量，和依然小于 $10^6$ 的要求，就是无解。
## PART3 代码

```cpp
#include<iostream>
using namespace std;
long long T,a1,a2,a3,a4,b1,b2,b3,b4,c1,c2,c3,c4,d1,d2,d3,d4,n,ans1,ans2,ans3,ans4,x;
int main()
{
  cin>>T;
  x=T;
  while(T--)
  {
    n=1000000;
    cin>>a1>>b1>>c1>>d1>>a2>>b2>>c2>>d2>>a3>>b3>>c3>>d3;
    //取每个对应的最大可能
    a4=min(min(a1,a2),a3);
    b4=min(min(b1,b2),b3);
    c4=min(min(c1,c2),c3);
    d4=min(min(d1,d2),d3);
    //处理第一个元素
    if(n>=a4)//如果不足就取最大
    {
      ans1=a4;
      n-=a4;//求还要多少
    }
    else//如果多了就取需要的
    {
      ans1=n;
      n=0;
    }
    //处理第二个元素
    if(n>=b4)
    {
      ans2=b4;
      n-=b4;
    }
    else
    {
      ans2=n;
      n-=n;
    }
    //处理第三个元素
    if(n>=c4)
    {
      ans3=c4;
      n-=c4;
    }
    else
    {
      ans3=n;
      n-=n;
    }
    //处理第四个元素
    if(n>=d4)
    {
      ans4=d4;
      n-=d4;
    }
    else
    {
      ans4=n;
      n=0;
    }
    //若每个位置都取了最大量而和依然不足就是无解。
    if(n)cout<<"Case #"<<x-T<<": "<<"IMPOSSIBLE"<<endl;
    else cout<<"Case #"<<x-T<<": "<<ans1<<" "<<ans2<<" "<<ans3<<" "<<ans4<<endl;
  }
  return 0;
}
```
## 结语
~~本题解由本人亲自编写，引用请注明来源。~~

抄题解可耻，请勿直接复制。

---

## 作者：ouxiyao (赞：0)

[船松门](https://www.luogu.com.cn/problem/P12980)
# P12980 [GCJ 2022 Qualification] 3D Printing
GCJ的题时限与空限永远很大。但是亲测爆搜会炸：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1000000;
struct node{int x,y,z,u;}a[4];
bool f;
void fourforsearch(){
    int l;
    for(int i = 0;i<=N;i++){
        if(i>a[1].x||i>a[2].x||i>a[3].x)continue;
        a[0].x = i;
        for(int j = 0;i+j<=N;j++){
            if(j>a[1].y||j>a[2].y||j>a[3].y)continue;
            a[0].y = j;
            for(int k = 0;i+j+k<=N;k++){
                if(k>a[1].z||k>a[2].z||k>a[3].z)continue;
                a[0].z = k;
                l = N-i-j-k;
                if(l>a[1].u||l>a[2].u||l>a[3].u)continue;
                a[0].u = l;
                f = 1;
                return ;
            }
        }
    }
    return ;
}
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
    int T,f;
    cin>>T;
    for(int o = 1;o<=T;o++){
        f = 0;
    	for(int i = 1;i<=3;i++)cin>>a[i].x>>a[i].y>>a[i].z>>a[i].u;
        fourforsearch();
        cout<<"Case #"<<o<<": ";
        if(f)cout<<a[0].x<<' '<<a[0].y<<' '<<a[0].z<<' '<<a[0].u<<'\n';
		else cout<<"IMPOSSIBLE\n";
	}
	return 0;
}
```
恶搞结束，下面开始正解。                    
我们求出每部分颜色最多可以为多少个单位，然后求和。如果和不够 $10^6$，说明无解了，输出 `IMPOSSIBLE`。        
否则，我们就让青色墨水尽量多的用，不能用了就用品红色墨水，以此类推，直到 $10^6$ 单位墨水全用完。       
跟爆搜很像：
```cpp
f = int(1e6);
if(f>xx)a[0].x = xx,f-=xx;
else a[0].x = f,f = 0;
if(f>yy)a[0].y = yy,f-=yy;
else a[0].y = f,f = 0;
if(f>zz)a[0].z = zz,f-=zz;
else a[0].z = f,f = 0;
if(f>uu)a[0].u = uu,f-=uu;
else a[0].u = f,f = 0;
```
完整代码（马蜂稍乱）：

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{int x,y,z,u;}a[4];//青，品红，黄，黑
int main(){
	cin.tie(0)->sync_with_stdio(0);
	cout.tie(0);
    int ls,T,xx,yy,zz,uu,f;
    cin>>T;
    for(int o = 1;o<=T;o++){
    	xx = yy = zz = uu = 2147483647;
    	for(int i = 1;i<=3;i++){
    		cin>>a[i].x>>a[i].y>>a[i].z>>a[i].u;
    		xx = min(a[i].x,xx);//求每种颜色最多多少单位
    		yy = min(a[i].y,yy);
    		zz = min(a[i].z,zz);
    		uu = min(a[i].u,uu);
		}
		cout<<"Case #"<<o<<": ";
		if(xx+yy+zz+uu>=int(1e6)){//见上
			f = int(1e6);
			if(f>xx)a[0].x = xx,f-=xx;
			else a[0].x = f,f = 0;
			if(f>yy)a[0].y = yy,f-=yy;
			else a[0].y = f,f = 0;
			if(f>zz)a[0].z = zz,f-=zz;
			else a[0].z = f,f = 0;
			if(f>uu)a[0].u = uu,f-=uu;
			else a[0].u = f,f = 0;
			cout<<a[0].x<<' '<<a[0].y<<' '<<a[0].z<<' '<<a[0].u<<'\n';
		}
		else cout<<"IMPOSSIBLE\n";
	}
	return 0;
}

```

---

