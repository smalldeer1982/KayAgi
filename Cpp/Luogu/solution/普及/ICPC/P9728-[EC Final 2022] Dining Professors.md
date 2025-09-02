# [EC Final 2022] Dining Professors

## 题目描述

庞教授邀请了 $n$ 位教授参加他的宴会。教授们坐在一个圆桌周围。对于所有 $i$，从 $1$ 到 $n$，教授 $i$ 坐在教授 $(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 旁边。

庞教授准备了 $n$ 道菜。桌子上有 $n$ 个位置。位置 $i$ 在教授 $i$ 的前面。教授 $i$ 只能接触到放在位置 $i$、$(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 处的菜。庞教授将在每个位置上放置一道菜。

在这些菜中，有 $a$ 道是辣的，$n-a$ 道是不辣的。有些（可能为 $0$）教授不能吃辣的食物。如果一位教授可以吃辣的食物，他/她的**满意度水平**是他/她可以接触到的菜的数量（无论是辣的还是不辣的）。如果一位教授不能吃辣的食物，他/她的满意度水平是他/她可以接触到的不辣的菜的数量。

庞教授知道每位教授是否可以吃辣的食物。请帮助他安排桌子上的菜，使得所有教授的满意度水平之和最大化。输出最大的总和。

## 样例 #1

### 输入

```
5 2
1 0 1 0 1
```

### 输出

```
13
```

# 题解

## 作者：zhouxianzhuo (赞：11)

本题解原已通过，后进行更新，请管理员通过，谢谢。

update on 2024.7.13
# 题目大意 ：
庞教授邀请了 $n$ 名教授坐在一张圆形的桌上吃饭，每个教授只能吃到自己左边、右边、面前的菜。

庞教授有 $n$ 盘菜，其中有 $a$ 盘菜是辣的，$(n-a)$ 盘是不辣的。庞教授知道每位教授的喜好（能吃辣或不能吃辣）,想求这些教授对菜品的满意度之和（每一位教授的满意度为他能吃的菜的数量）。

**注意：能吃辣的教授可以吃不辣的菜。**
# 思路:
由于这道题要求满意度的最大值，所以考虑使用贪心。先根据每位教授的喜好计算优先值，再根据优先值确定哪些位置的菜是辣的，最后计算满意度总和就行了。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b[100010],f[100010],id[100010],d[100010],ans;
//f[i]表示第i盘菜的优先级 
//id[i]表示优先级排序后，排在第i的优先值所对应的菜 原本的位置 
//d[i]表示第i盘菜的味道（0为不辣，1为辣） 
bool p(int x,int y){
	return f[x]==f[y]?x<y:f[x]>f[y];
	//按 "优先级大的排前面；优先级相等的，编号越小越前" 的顺序排序 
}
int main(){
	cin>>n>>a;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
		if(b[i])	//第i位教授能吃辣 
		{
			f[i%n+1]+=1;		//第(i%n+1)盘菜的优先级+1 
			f[i]+=1;			//第i盘菜的优先级+1 
			f[(i+n-2)%n+1]+=1;	//第((i+n-2)%n+1)盘菜的优先级+1 
		}
		else	//第i位教授不能吃辣 
		{
			f[i%n+1]-=1;		//第(i%n+1)盘菜的优先级-1 
			f[i]-=1;			//第i盘菜的优先级-1 
			f[(i+n-2)%n+1]-=1;	//第((i+n-2)%n+1)盘菜的优先级-1 
		}
		id[i]=i;	//第i盘菜的位置是i 
	}
	sort(id+1,id+1+n,p);	//对id进行排序 
	for(int i=1;i<=a;i++)
		d[id[i]]=1;			//排在前a的优先级所对应的菜全部设为辣的 
	for(int i=1;i<=n;i++)
	{
		if(b[i]==1)
		{
			ans+=3;
			continue;	//如果第i位教授能吃辣，则能够到的3盘菜都能吃，满意度为3 
		}
		if(d[i%n+1]==b[i])ans+=1;
		//如果第(i%n+1)盘菜符合第i名教授的口味，满意度+1 
		if(d[i]==b[i])ans+=1;
		//如果第i盘菜符合第i名教授的口味，满意度+1 
		if(d[(i+n-2)%n+1]==b[i])ans+=1;
		//如果第((i+n-2)%n+1)盘菜符合第i名教授的口味，满意度+1 
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：_Star_Universe_ (赞：8)

## [题目传送门](https://www.luogu.com.cn/problem/P9728)
看完了其他题解，总算学会了这道题，也来发一篇题解吧。
### 思路
算法：**贪心**。首先第 $i$ 位教授只能吃到面前的菜与相邻的两盘菜，即第 $i$ 盘菜、第 $(i \bmod n)+1$ 盘菜和第 $((i+n-2) \bmod n)+1$ 盘菜。对于能吃辣的教授来说，满意度一定为 $3$；对于不能吃辣的教授来说满意度为能吃到的不辣的菜的数量。

最好的情况就是所有人都能吃辣，即最大满意度为 $3 \times n$。我们可以用数组统计不能吃辣的人数并升序排列，然后圆桌的前 $a$ 个位置放辣的菜，后 $n-a$ 个位置放不辣的菜，易证这样是最优策略。定义一个变量 $ans$ ，从第 $1$ 个位置遍历到第 $a$ 个位置，每次将 $ans$ 加 $1$，最后输出 $3 \times n-ans$ 即可。

从[这篇题解](https://www.luogu.com.cn/article/64bgcauq)里学到了由于圆桌是一个环，要有这么一句代码：
```c
i[0]=i[n];i[n+1]=i[1];
```

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,a,ans,i[100005],z[100005];
signed main(){
    cin>>n>>a;
    for(int k=1;k<=n;k++){
		cin>>i[k];
	}
    i[0]=i[n];i[n+1]=i[1];
    for(int k=1;k<=n;k++){
    	for(int j=k-1;j<=k+1;j++){
    		if(i[j]!=1){
				z[k]++;
			}
		}
    }
    sort(z+1,z+n+1);
    for(int k=1;k<=a;k++){
    	ans+=z[k];
    }
    cout<<3*n-ans;
    return 0;
}
```
因为本蒟蒻是跟着其他题解学习的，可能有部分内容相似，如有侵权立即撤下。

---

## 作者：天使宝贝 (赞：3)

[题面传送门](https://www.luogu.com.cn/problem/P9728)

### 题目简述

有 $n$ 个人围成一桌，每个人的面前都有一道菜，其中辣菜有 $a$ 道，不辣的菜有 $n - a$ 道，每个人只能吃到自己左边一个人的，自己前面的，以及右边一个人的菜，每个人是否吃辣用 $0$ 或 $1$ 表示，$0$ 表示这个人不吃辣，$1$ 表示这个人吃辣。能吃辣的人的满意度是 $3$ 分，而不能吃辣的人的满意度则等于可以吃到的不辣的菜的数量，答案要求最高的满意度和。

### 思路&分析

稍加分析即可发现，这是一道简单的贪心题，我们只需要考虑每道菜对不能吃辣的人能产生多少贡献，让贡献较少的是辣菜，贡献大的则为不辣的菜即可。

### Code
```cpp
#include <bits/stdc++.h>
#define ll long long
#define IOS ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
using namespace std;
const int MAXN = 1e5 + 5;
int n, a, b[MAXN], t[MAXN], ans;
int main()
{
    IOS;  // 读入加速
    cin >> n >> a;
    ans = n * 3;
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    b[0] = b[n];  // 由于是围成一桌，所以要让其首尾相连
    b[n + 1] = b[1];
    for (int i = 1; i <= n; i++)
    {
        if (b[i - 1] == 0)  // 计算每道菜能产生的贡献
            t[i]++;
        if (b[i] == 0)
            t[i]++;
        if (b[i + 1] == 0)
            t[i]++;
    }
    sort (t + 1, t + n + 1);
    for (int i = 1; i <= a; i++)  // 减掉所有的不能吃辣的人能吃到的辣菜
        ans -= t[i];
    cout << ans << endl;  // 输出答案
    return 0;  // 好习惯
}
```
求管理员通过。

---

## 作者：skyskyCCC (赞：2)

## 前言。
又是这次镜像赛唯二做出来的题。
## 分析。
~~话说为什么这场没有中文翻译了啊。~~  
题意概诉：庞教授邀请了 $n$ 位教授参加他的宴会。教授们坐在圆桌旁。对所有从 $1$ 到 $n$ 的第 $i$ 个教授，教授 $i$ 和第 $\left(i\bmod n\right)+1$ 与第 $\left(\left(i+n-2\right)\bmod n\right)+1$ 教授相邻，且一个教授只能吃一盘菜，可以吃的菜也符合上面的排位。在这些菜肴中，其中有 $a$ 种是辣的，其它 $n-a$ 种是不辣的。一些教授是不能吃辣的。如果一个教授可以吃辣，那么这个教授的满意度就是他能吃到的菜的数量，此时**不区分辣菜还是不辣菜**。如果教授不能吃辣，他的满意程度就是他能吃到的**不辣**的菜的数量。求出最大的满意度。

考虑每盘菜是辣或者不辣，分别能有多少教授吃。因为我们考虑到能吃辣的教授可以吃任何菜，所以我们希望能吃的教授尽量多，所以就按照每盘菜如果是辣的，将能吃辣的教授数，从多到少排序即可。

找出最大的几盘辣菜，然后统计出不辣菜就是答案。

详情可以根据代码了解。

代码如下，仅供参考：
```
#include<iostream>
#include<algorithm>
using namespace std;
int n,a,b[100005];
int ans,t[100005];
bool cmp(int f,int s){
	return f>s;
}
int main(){
    cin>>n>>a;
    for(int i=1;i<=n;i++){
        cin>>b[i];
        if(b[i]==1){//如果这个教授能吃辣。
        	t[i]++;
        	t[(i%n)+1]++;
            t[(i+n-2)%n+1]++;//他能吃的菜统计一下。
        }
    }
    sort(t+1,t+1+n,cmp);//排序。
    for(int i=1;i<=a;i++){
	    ans+=t[i];//加上所有的辣菜可以吃的最大人数。
	}
    ans+=3*(n-a);//加上所有的不辣菜可以吃的人数。
    cout<<ans<<"\n";
    return 0;
}
```
## 后记。
大家如有疑问，可以在评论区提出，我会尽力解答的。

---

## 作者：11216216c (赞：1)

## 题目大意
庞教授邀请了 $ n $ 位教授参加他的宴会。教授们坐在一个圆桌周围。庞教授准备了 $ n $ 道菜，这些菜有些是辣的，有些菜是辣的。桌子上有 $ n $ 个位置。位置 $ i $ 在教授 $ i $ 座位的前面。庞教授将在每个位置上放置一道菜。教授**只能接触到放在位置左边、右边和面前的菜**，在 $ n $ 个教授中有 $ a $ 个可以吃辣，**所以我们需要求出是哪 $ a $ 教授可以吃辣**。
## 做题方案
  这是一道贪心题，第一步先算出每个位置是放辣的贡献，然后用快排挑出贡献最大的 $ a $ 盘菜把这些菜变成辣的，即可算出哪几盘是辣菜，再把 $ n $ 个人遍历一遍，利用假设，假设所有人都喜欢自己面前的三盘菜则满意度为 $ n $ 的 $ 3 $ 倍，但是最后的结果不一定是最优解，所以要判断第 $ i $ 位教授是否讨厌面前的菜，如果讨厌则满意度减一。
下面见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b[100001],ans;
bool f[100001];
struct yu //结构体，方便快排。
{
	int x,id;
}x[100001];
bool cmp(yu xx,yu yy)//cmp是我自定义快排的函数。
{
	return xx.x>yy.x;
}
int main()
{
	scanf("%d%d",&n,&a);
	for(int i=1;i<=n;i++) {
		scanf("%d",&b[i]);
		x[i].id=i;//保存满意度水平的位置。
	}
	for(int i=1;i<=n;i++)
	{
		if(b[i]==0) continue;
		else{
			x[i%n+1].x++;
			x[i].x++;
			x[(i+n-2)%n+1].x++;
//如果这个教授能吃辣，就让这个教授能拿到的菜辣度加一。
		}
	}
	sort(x+1,x+n+1,cmp);//快排选出辣度最高的菜。
	for(int i=1;i<=n;i++)
	if(a>0){
		f[x[i].id]=true;//哪些菜该是辣的。
		a--;
	}
	ans=n*3;//最好的情况。
	for(int i=1;i<=n;i++)
	if(b[i]==0)//表明该教授不吃辣。
	{
		if(b[i]!=f[i%n+1]) ans--;
		if(b[i]!=f[i]) ans--;
		if(b[i]!=f[(i+n-2)%n+1]) ans--;
    //由于教授不吃辣，但周围又有菜是辣的所有满意度减一。
	}
	printf("%d",ans);
}
```

---

## 作者：EityDawn (赞：1)

# 题面描述
庞教授有 $n$ 盘菜，其中 $a$ 盘是辣的，$n-a$ 是不辣的，现给出教授们吃辣或不吃辣的习惯，教授只能取到 $(i \bmod n)+1$，$i$ 和 $((i+n-2)\bmod n)+1 $ 处的菜品，能吃辣的人的满意程度是能取到的菜品数量，不吃辣的人的满意程度是能取到不辣菜的数量，求摆放菜品使教授们的满意程度最大。
# 解题思路
挺简单的一道贪心题，首先我们对每一个摆菜位置初始一个优先级，即统计每个位置上不吃辣的人数，记录在数组里，按降序进行排序，然后将前 $n-a$ 个位置摆上不辣菜，即可保证不吃辣教授的满意程度最大。
****
## 上 code
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e6;
int s[N];
struct node{
	int num,ord;
	bool operator <(const node &a) const
	{
		return num>a.num;//升序排列
	}
} mk[N];
bool k[N];
int main() {
   int n,a;
   cin>>n>>a;
   for (int i=1;i<=n;++i)
       cin>>s[i];
   int b=n-a;int p=0;
   for(int i=1;i<=n;i++)
	if(!s[i]) mk[i].num++,mk[i%n+1].num++,mk[(i+n-2)%n+1].num++;
	for(int i=1;i<=n;i++) mk[i].ord=i;//记录位置
	sort(mk+1,mk+1+n);
	for(int i=1;p!=n-a;i++,p++) k[mk[i].ord]=1;//开始摆菜
	int ans=0;
	for(int i=1;i<=n;i++)//下面便是纯模拟了
	{
		if(s[i]==1)
			ans+=3;
		else ans+=k[i],ans+=k[i%n+1],ans+=k[(i+n-2)%n+1];
	}
	cout<<ans;
    return 0;
}
```

---

## 作者：ZJle (赞：1)

非常简单的贪心题
  
  考虑每盘菜辣或者不辣,分别能有多少人吃,并且吃的人数要尽量多,那么可以按照如果能吃和吃的人数往里面放即可。

 时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
const int N = 1e5 + 5;
using namespace std;
int n, a, b[N], k[N];
int main()
{
    // freopen("M.in","r",stdin);
    // freopen("M.out","w",stdout);
    cin >> n >> a;
    int ans = 3 * n;
    for (int i = 0; i < n; i++)
    {
        cin >> b[i];
    }
    for (int i = 0; i < n; i++)
    {
        k[i] = b[(i + n - 1) % n] + b[i] + b[(i + 1) % n] - 3;
    }
    partial_sort(k, k + a, k + n, greater<int>());
    for (int i = 0; i < a; i++)
        ans += k[i];
    cout<<ans;
}
```


---

## 作者：HFanGDoDM (赞：1)

# 题意简述

给定一个长度为 $n$ 的 $0/1$ 序列 $b$，并给定另一个长度为 $n$ 的 $0/1$ 序列 $c$ 中 $1$ 的数量 $a$。定义一个长度为 $n$ 的序列 $s$，其中 $s_i$ 的计算公式如下：

$$s_i=\begin{cases}
3,b_i=1,\\
[c_i=0]+[c_{i\bmod n+1}=0]+[c_{(i+n-2)\bmod n+1}=0],b_i=0
\end{cases}$$

试求出在所有可能的序列 $c$ 对应产生的序列 $s_i$ 中，$\displaystyle\sum_{i=1}^ns_i$ 的最大值。

### 数据范围

$3\leqslant n\leqslant 10^5,0\leqslant a\leqslant n,b_i\in\{0,1\}$。

# 解题思路

### 做法

定义序列 $f$，其中 $f_i=[b_i=0]+[b_{i\bmod n+1}=0]+[b_{(i+n-2)\bmod n+1}=0]$。

对序列 $f$ 按照 **由小到大** 的顺序排序，则答案

$$(\displaystyle\sum_{i=1}^ns_i)_{\max}=3n-\displaystyle\sum_{i=1}^af_i$$

### 正确性证明

我们考虑一个位置 $i$，确定 $c_i=0$ 还是 $c_i=1$。根据题意，若 $c_i=0$，则该位置填的数对答案的贡献为 $3$。否则，该位置填的数对答案的贡献为 $[b_i=1]+[b_{i\bmod n+1}=1]+[b_{(i+n-2)\bmod n+1}=1]\leqslant 3$。

因此，假设不存在 $a$ 的限制，则可以发现，**一个位置填 $0$ 一定比填 $1$ 不劣**。所以，不存在 $a$ 的限制时，答案为 $3n$。

对于两个位置 $i,j(i\not=j)$，由于 $b$ 序列是恒定不变的，因此 $i,j$ 两个位置填的数分别对答案的贡献是 **互不影响** 的，或者说是 **相互独立** 的。因此，我们可以考虑，对于每个填的 $1$，都要让其 **减少的对答案的贡献尽可能少**。由上述推理，其减少的对答案的贡献即为 $[b_i=0]+[b_{i\bmod n+1}=0]+[b_{(i+n-2)\bmod n+1}=0]=f_i$。

因此，每次需要选择 **最小的** $f_i$，使得每次减少的贡献尽可能少。

所以，这一思路是正确的。

### 具体实现

读入 $b$ 数组，并计算 $f_i=[b_i=0]+[b_{i\bmod n+1}=0]+[b_{(i+n-2)\bmod n+1}=0]$。

对 $f_i$ 从小到大排序，求出 $f$ 数组的前 $a$ 项和，输出答案 $ans=3n-\displaystyle\sum_{i=1}^af_i$。

### 时间复杂度分析

计算 $f$ 数组，时间复杂度 $O(n)$。对 $f$ 数组排序，时间复杂度 $O(n)$ 或 $O(n\log n)$，因排序实现方法而异。求和时间复杂度为 $O(a)$。

总时间复杂度 $O(n\log n)$ 或 $O(n)$，可以通过本题。

### 参考核心代码

本代码使用的是 $O(n\log n)$ 的实现方式。

```cpp
for(i=1;i<=n;i++)
    num0[i]=(!b[i])+(!b[i%n+1])+(!b[(i+n-2)%n+1]);//计算上述的f数组
sort(num0+1,num0+1+n);//从小到大排序
FM ans=n*3;
for(i=1;i<=a;i++)
    ans-=num0[i];//计算答案
printf("%d",ans);
```

---

## 作者：huyangmu (赞：1)

考虑使用贪心。

如果这个教授可以吃辛辣的食物，就直接把答案加三。

然后贪心处理不能吃辛辣食物的教授。

如果在某个位置放了不辛辣的食物，这个食物只会影响到这个位置，这个位置

左边相邻的位置，这个位置右边相邻的位置。我们可以定义任意一个位置的影

响度为这三个位置中不吃辛辣食物的教授个数。

因为要让满意度尽可能大，所以优先考虑在影响度大的位置上放置不辛辣食

物，直到放完所有不辛辣食物。

如果每个位置都被放了不辛辣食物后还有不辛辣食物没放完，就是每个位置的

影响度都是三，直接输出总教授数乘三。

还要特判如果一个不辛辣食物都没有，直接输出可以吃辛辣食物的教授个数乘三。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int NR=1e5+5;
int n,k,a[NR],ans,b[NR];
signed main (){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	for (int i=1;i<=n;++i) cin>>a[i];
	for (int i=1;i<=n;++i){		
		if (a[i]) ans+=3;//统计能吃辛辣食物的教授满意度。
	}
	k=n-k;
	if (k==0){
		cout<<ans<<'\n';
		return 0;
	}//特判。
	for (int i=1;i<=n;++i){
		int tmp1=(i%n)+1;
		int tmp2=((i+n-2)%n)+1;
		int cnt=0;
		if (a[tmp1]==0) ++cnt;
		if (a[i]==0) ++cnt;
		if (a[tmp2]==0) ++cnt;
		if (cnt==3&&b[i]==0){//影响度=3。
			b[i]=1;
			--k;		
		}
		if (k==0) break;
	}
	if (!k){
		for (int i=1;i<=n;++i){
			if (a[i]) continue;
			int tmp1=(i%n)+1;
			int tmp2=((i+n-2)%n)+1;
			int cnt=0;		
			if (b[tmp1]==1) ++ans;
			if (b[i]==1) ++ans;
			if (b[tmp2]==1) ++ans;
		}
		cout<<ans<<'\n';
		return 0;
	}
	for (int i=1;i<=n;++i){
		int tmp1=(i%n)+1;
		int tmp2=((i+n-2)%n)+1;
		int cnt=0;
		if (a[tmp1]==0) ++cnt;
		if (a[i]==0) ++cnt;
		if (a[tmp2]==0) ++cnt;
		if (cnt==2&&b[i]==0){//影响度=2。
			b[i]=1;
			--k;		
		}
		if (k==0) break;
	}
	if (!k){
		for (int i=1;i<=n;++i){
			if (a[i]) continue;
			int tmp1=(i%n)+1;
			int tmp2=((i+n-2)%n)+1;
			int cnt=0;	
			if (b[tmp1]==1) ++ans;
			if (b[i]==1) ++ans;
			if (b[tmp2]==1) ++ans;
		}
		cout<<ans<<'\n';
		return 0;
	}
	for (int i=1;i<=n;++i){
		int tmp1=(i%n)+1;
		int tmp2=((i+n-2)%n)+1;
		int cnt=0;
		if (a[tmp1]==0) ++cnt;
		if (a[i]==0) ++cnt;
		if (a[tmp2]==0) ++cnt;
		if (cnt==1&&b[i]==0){//影响度=1。
			b[i]=1;
			--k;			
		}
		if (k==0) break;
	}
	if (!k){
		for (int i=1;i<=n;++i){
			if (a[i]) continue;
			int tmp1=(i%n)+1;
			int tmp2=((i+n-2)%n)+1;
			int cnt=0;	
			if (b[tmp1]==1) ++ans;
			if (b[i]==1) ++ans;
			if (b[tmp2]==1) ++ans;
		}
		cout<<ans<<'\n';	
		return 0;
	}
	cout<<n*3;//最后输出。
	return 0;
}


---

## 作者：__bjxx0201__ (赞：0)

## 题目大意

教授请了 $n$ 个人围坐在一圈上吃饭。每一个人只能吃到自己左边、右边、前面的菜。

教授恰好也有 $n$ 盘菜，其中有 $a$ 盘是辣的，其余的都是不辣的。能吃辣的人满意度可以加上 $3$，不能吃辣的人的满意度为可以吃到的菜（也就是不辣的菜的总数）。试求出这些人对于菜品的满意程度的最大值。

设 $0$ 为不能吃辣的人，$1$ 为能吃辣的人。

**不能吃辣的人不能吃辣的菜，能吃辣的人既能够吃辣的菜，也能够吃不辣的菜。**

## 思路

[题目传送门](https://www.luogu.com.cn/problem/P9728)

看到“最大值”，就知道是贪心思想。

由于不辣的菜所有人都可以吃，所以我们就要关注辣的菜。

对于一盘辣的菜，它左边相邻的位置、右边相邻的位置、前面相邻的位置的人就需要判断，它的贡献就是左边或者右边、前面能吃辣的人的数量。

所以，一开始我们假定所有辣的菜都能够有贡献，答案就是 $n\times 3$。

接下来我们枚举每一个位置，查看是否能够做出贡献，将每一个位置做出的贡献保存在一个数组中。

由于是要求出最大的贡献，所以需要从小到大排序贡献数组，由一开始的 $n\times 3$ 减去开头的 $a$ 个贡献值就可以了，这样就可以使得答案最大。

**注意：由于是一个环，所以我们需要合并这个环数组。**

参考代码：

```
#include <bits/stdc++.h>
using namespace std;
int n,k,ans,a[100100],f[100100];
int main() {
	cin>>n>>k;
    for (int i=1;i<=n;i++) {
    	cin>>a[i];
    	if (a[i]==0) f[i]++;
	}
	a[0]=a[n],a[n+1]=a[1];//处理环的问题。
	for (int i=1;i<=n;i++) {
		if (a[i-1]==0) f[i]++;//计算当前左右菜品的贡献。
		if (a[i+1]==0) f[i]++;
	}
	sort (f+1,f+n+1);
	for (int i=1;i<=k;i++) ans+=f[i];//贪心。
	cout<<n*3-ans;
	return 0;
}
```

---

## 作者：Dream_Stars (赞：0)

## 题意说明：
有 $n$ 个教授，其中有一些教授可以吃辣，一些不可以，而有 $a$ 道菜是辣的，有 $n-a$ 道菜是不辣的，每个教授可以接触到的菜是与自己相邻的菜，如教授的位置是 $i$，则他可以接触到菜的位置是 $i-1$，$i$，$i+1$，而可以吃辣的教授的满意度一定是 $3$，而不可以吃辣的教授的满意度是可以接触到不辣的菜之和。要求我们重新安排桌子上菜的摆放方式，让满意度**尽量高**。

## 算法解释：
这道题目看起来很难，其实上就是一个贪心的题目，我们可以算出每一个位置放置辣菜的贡献，最后一个排序，算出辣菜贡献的总和即可，最后输出加上不辣菜的贡献。但是要注意一点，因为题面里提到了是一个环，所以需要注意贡献计算的**环**处理。

## 代码展示：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
long long x , n , m , ans , a[N];
bool cmp(int a,int b){//快速排序从大到小排序的cmp。
  return a > b;
}
int main()
{
  scanf("%lld%lld" , &n , &m);
  for(int i = 1 ; i <= n ; i++){
  	scanf("%lld" , &x);
  	if(x == 0) continue;//如果教授不能吃辣，直接跳过，他对于辣菜没有任何贡献。
    a[i]++;
    if(i == n) a[1]++;
    else a[i+1]++;
    if(i == 1) a[n]++;//这里是环的处理。
    else a[i-1]++;
//计算辣菜的贡献。
  }
  sort(a + 1 , a + n + 1 , cmp);//进行排序。
  for(int i = 1 ; i <= m ;i ++) ans = ans + a[i];//计算出辣菜的总贡献的贡献。
  cout<<ans + (n - m) * 3;//输出前面计算的ans以及不辣菜的贡献即可。
  return 0;//return 养成好习惯。
}
```

---

## 作者：wangzc2012 (赞：0)

# P9728 [EC Final 2022] Dining Professors
## 题意概括
有 $n$ 名教授坐在圆桌旁，你有 $n$ 盘菜，其中有 $a$ 盘是辣的，$(n-a)$ 盘是不辣的，每个人只能取到他前面、左边和右边的菜。同时，你还知道每位教授能否吃辣，能吃辣的人的满意度水平是他能取到的菜品数量，不能吃辣的人的满意度水平是他能取到的不辣的菜品数量。你可以任意摆放菜品，求所有教授的满意度水平之和最大为多少。
## 思路分析
一道贪心题。  
首先，计算把不辣的菜每个位置的贡献，将贡献排序，根据贪心，把不辣的菜放到贡献最大的地方，然后计算所有人的满意度水平。
## 算法实现
本题如果我们按照正常的思路，不断累加所有人的满意度水平会很麻烦，因此，我们考虑用最大可能的满意度水平减去不能吃辣的人的不满意水平。  
首先，我们知道最大可能的满意度水平是所有人都满意，即 $n \times 3$。  
接着，计算把不辣的菜放到每个位置的贡献并排序，将所有不辣的菜放到贡献最大的地方。  
最后，减去不能吃辣的人的不满意水平。由于只有 $(n-a)$ 盘不辣的菜，所以会有 $a$ 个人可能不满意，同时，由于不辣的菜被放到了贡献最大的位置，所以这 $a$ 个可能不满意的人就在贡献最小的 $a$ 个位置上。而不辣的菜对这几个位置没有贡献，但实际上一开始我们假设是有贡献的，因此减去不辣的菜对这 $a$ 个位置的贡献即可。
## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b[100005],g[100005],ans;  //人数，辣菜数量，能否吃辣，不辣的菜的贡献，答案
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);    //优化
    cin>>n>>a;
    ans=n*3;    //假设每个人的满意度都为3
    for (int i=1;i<=n;i++) cin>>b[i];    //输入
    b[0]=b[n];b[n+1]=b[1];    //圆桌，特殊处理
    for (int i=1;i<=n;i++){    //不辣的菜放到第i个位置产生的贡献
        if (b[i-1]==0) g[i]++;    //左边
        if (b[i]==0) g[i]++;    //当前位置
        if (b[i+1]==0) g[i]++;    //右边
    }
    sort(g+1,g+n+1);    //从小到大排序
    for (int i=1;i<=a;i++) ans-=g[i];    //遍历所有辣菜，减去不能吃辣的人的不满意度
    cout<<ans;    //输出答案
    return 0;    //圆满结束
}
```

---

## 作者：TheForgotten (赞：0)

# P9728 [EC Final 2022] Dining Professors 题解
## 题目大意 
有 $a$ 道菜是辣的，$n-a$ 道是不辣的。知道每位教授是否可以吃辣的食物。如果一位教授可以吃辣的食物，**满意度水平**是可以接触到的菜的数量。如果一位教授不能吃辣的食物，满意度水平是可以接触到的不辣的菜的数量。请安排桌子上的菜使得所有教授的满意度水平之和最大化。

## 思路
考虑贪心。

答案为 $n\times3$ 减去每道菜对满意度影响总值，所以尽量少减不能吃辣人数。
累加不能吃辣人数和可吃辣人数，统计每个位置上不吃辣的人数，按降序排序，在前面 $n-a$ 道菜摆不辣的菜即可。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,x,sum;
const int y=100005;
int a[y],cnt[y];
signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++) cin>>a[i];
    a[0]=a[n],a[n+1]=a[1];
    for(int i=1;i<=n;i++){
    	for(int j=i-1;j<=i+1;j++){
    		if(!a[j])cnt[i]++;//累加不能吃辣人数 
		}
    }
    sort(cnt+1,cnt+1+n);//排序
    for(int i=1;i<=x;i++) sum+=cnt[i];
    cout<<3*n-sum;
    return 0;
}
```

---

## 作者：Tjl0427 (赞：0)

## 题解：P9728 [EC Final 2022] Dining Professors
[题目传送门](https://www.luogu.com.cn/problem/P9728)
### 题目简述
$n$ 个人围成一桌，每人面前都有 $1$ 道菜，$a$ 道 辣的，$n - a$ 道不辣的，每个人可以吃到自己前面、左边和右边的菜。能吃辣用 $1$ 表示，不能吃辣用 $0$ 表示。

**能吃辣**的人的满意度是 $3$ 分，**不能吃辣**的人的满意度则等于可以吃到的不辣的菜的数量，**答案**：最高的满意度和。

### 分析
这是一道贪心题。

统计每个位置上不吃辣的人数，按降序排序，在前面 $n - a$ 道菜摆不辣的菜就行了。

### 代码
```c
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+1;
int s[N];
struct node{
	int num,order;
	bool operator <(const node &a) const{
		return num>a.num;
	}
}man[N];
bool k[N];
int main(){
	int n,a,b,p=0,ans=0;
	cin>>n>>a;
	for(int i=1;i<=n;++i)cin>>s[i];
	b=n-a;
	for(int i=1;i<=n;i++)if(!s[i]) man[i].num++,man[i%n+1].num++,man[(i+n-2)%n+1].num++;
	for(int i=1;i<=n;i++)man[i].order=i;
	sort(man+1,man+1+n);
	for(int i=1;p!=n-a;i++,p++)k[man[i].order]=1;
	for(int i=1;i<=n;i++)
		if(s[i]==1)ans+=3;
		else ans+=k[i],ans+=k[i%n+1],ans+=k[(i+n-2)%n+1];
	cout<<ans<<"\n";
	return 0;
}
```

---

## 作者：PengDave (赞：0)

# solution
考虑贪心。有不吃辣的教授可以接触到的座位选择不辣的菜的优先值更高，接着对优先值进行排序，优先值最高的前 $n-a$ 个座位选择不辣的。最后计算每个教授的满意度相加即可。
# code
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int s[100010],mp[100010],b[100010];
bool cmp(int x,int y){
	if(s[x]!=s[y]){
		return s[x]>s[y];
	}else{
		return x<y;
	}
}
int main(){
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int n,a;
	cin>>n>>a;
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	for(int i=1;i<=n;i++){
		if(b[i]){
			s[i]--;
			s[i%n+1]--;
			s[(i+n-2)%n+1]--;
		}else{
			s[i]++;
			s[i%n+1]++;
			s[(i+n-2)%n+1]++;
		}
		mp[i]=i;
	}
	sort(mp+1,mp+1+n,cmp);
	fill(s+1,s+1+n,0);
	for(int i=1;i<=n-a;i++){
		s[mp[i]]=1;
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		if(b[i]){
			ans+=3;
		}else{
			if(s[i]){
				ans++;
			}
			if(s[i%n+1]){
				ans++;
			}
			if(s[(i+n-2)%n+1]){
				ans++;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Thorongil_Gondor (赞：0)

# P9728 \[EC Final 2022\] Dining Professors 题解
## 思路
两种情况：
* 可以吃辣，满意度为此教授能吃到的菜的数量，不区分辣菜还是不辣菜。
* 不能吃辣，满意程度为此教授能吃到的不辣的菜的数量，求出最大的满意度。  

答案为 $n\times3$ 减去每道菜对满意度影响总值，所以尽量少减不能吃辣人数。

由于圆桌是一个环，故要破环成链。

具体思路见代码注释。
## AC Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int n,x,sum;
int a[100005],cnt[100005];
signed main(){
    cin>>n>>x;
    for(int i=1;i<=n;i++)cin>>a[i];
    a[0]=a[n],a[n+1]=a[1];//破环成链
    for(int i=1;i<=n;i++){
    	for(int j=i-1;j<=i+1;j++){
    		if(!a[j])cnt[i]++;//累加不能吃辣人数 
		}
    }
    sort(cnt+1,cnt+1+n);//排序不能吃辣人数
    for(int i=1;i<=x;i++)sum+=cnt[i];//可吃辣人数 
    cout<<3*n-sum;
    return 0;
}
```

---

## 作者：lgydkkyd (赞：0)

# 思路
翻译完题目后可知，题目让我们求的是最大的满意程度，稍加分析便可以发现这是一道比较简单的贪心，贪心策略如下：三倍的 $n$ 减去每道菜产生的影响总值便是我们要的最终答案。
# 代码实现
第一步，我们可以创建数组 $number$ 记录第 $i$ 道菜产生的影响。第二步，我们以从小到大的规则即升序排序 $number$ 数组，并用变量 $he$ 记录 $number$ 数组的全值和。第三步，输出答案。
# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int s[100001],number[100001],n,x;
int main(){
    scanf("%d%d",&n,&x);//输入人数及辣菜数量 
    for(int i=1;i<=n;i++){
        scanf("%d",&s[i]);//输入数组 
    }
    //把链当成环来做 
    s[0]=s[n];//使头的前面连着尾 
    s[n+1]=s[1];//使尾的后面连着头 
    //接下来记录i的前后及自身不能吃辣的数量 
    for(int i=1;i<=n;i++){
    	for(int j=i-1;j<=i+1;j++){
    		if(s[j]==0)//当前不能吃辣 
    		number[i]++;//累加数量
		}
    }
    sort(number+1,number+1+n);//排序数量数组 
    int he=0;
    for(int i=1;i<=x;i++){//累加数量数组 
    	he+=number[i];
	}
    printf("%d",3*n-he);//输出答案 
    return 0;
}
```

---

## 作者：niuzh (赞：0)

### 题目大意

$n$ 个人围成一圈，每个人面前有一道菜，其中有 $a$ 道辣菜，每个人都有一个数字代表状态，$1$ 代表可以吃辣，$0$ 代表不能吃辣，每个人都只能吃到面前的，左边一个人的，右边一个人的菜。能吃辣的人的满意度一定等于 $3$ 分，而不能吃辣的人的满意度等于可吃到的不辣的菜的数量，求最高的满意度和。

### 思路

一道简单的贪心。

只用考虑每个菜能对不能吃辣的人所产生的贡献即可，让贡献少的为辣菜，大的为不辣菜。

### 代码

```
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int b[N],cnt[N];
int main()
{
	int n,a;
	cin>>n>>a;
	for(int i=1;i<=n;i++)
	{
		cin>>b[i];
	}
	b[0]=b[n];//头尾相连
	b[n+1]=b[1];
	for(int i=1;i<=n;i++)//计算贡献
	{
		if(b[i-1]==0)
		{
			cnt[i]++;
		}
		if(b[i]==0)
		{
			cnt[i]++;
		}
		if(b[i+1]==0)
		{
			cnt[i]++;
		}
	}
	sort(cnt+1,cnt+n+1);
	int ans=3*n;
	for(int i=1;i<=a;i++)//减去不能吃辣的人能吃到的辣菜
	{
		ans-=cnt[i];
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：guowenxuan101 (赞：0)

# 题目描述
庞教授邀请了 $n$ 位教授参加宴会。教授们坐在圆桌旁。对于从 $1$ 到 $n$ 的所有教授只能吃到 $(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 的菜。

桌子上有 $n$ 的位置。位置 $i$ 在教授 $i$ 前面。$i$ 教授只能访问放置自己位置上的和 $(i \bmod n) + 1$ 和 $((i + n - 2)\bmod n) + 1$ 位置的菜肴。庞教授将在每个位置放置一个盘子。

在这些菜中，$a$ 是辣的，$n-a$ 不是辣的。有些教授不能吃辣的食物。如果教授可以吃辣，他的满意度是他可以吃的菜（辣菜和不辣的数量）。如果教授不能吃辣，他的满意度是他能吃到的不辣菜肴的数量。

庞教授知道每个教授是否可以吃辣。
## 思路
统计辣菜放在每个位置可以被几个教授吃掉，排序一下，取放辣菜价值最大的前 $a$ 个位置，剩下的就放不辣菜。

## 注释代码
```
#include<bits/stdc++.h>
using namespace std;
int sum[114514];   //sum[i] 在i位置摆辣菜有sum[i]人可以吃到 
int max = -1000, tot,ans;
int main()
{
	int n, a;
	scanf("%d%d",&n,&a);  //输入 
	for(int i=1;i<=n;i++)
	{
		int b;
		scanf("%d",&b);   //输入教授可否吃辣 
		if(b)  //如果能吃辣，在哪些位置可以摆辣菜。 
		{
			sum[i]+=1;   // i位置摆辣菜可以吃到的人 +1。 
			sum[(i%n)+1]+=1;   // （i%n)+1 位置摆辣菜可以吃到的人 +1。 
			sum[(i+n-2)%n+1]+=1;   // (i+n-2)%n+1 位置摆辣菜可以吃到的人 +1。 
		}
	}
	sort(sum+1,sum+n+1);   //排序 
	ans += (n - a)*3;   //每个人都可以吃不辣的菜，所以 *3 
	for(int i=n;i>=n-a+1;i--) ans += sum[i];  //加上摆a个辣菜的最大价值 
	printf("%d",ans); 
	return 0;  
} 
```
### 代码
```
#include<bits/stdc++.h>
using namespace std;
int sum[114514];  
int max = -1000, tot,ans;
int main()
{
	int n, a;
	scanf("%d%d",&n,&a);
	for(int i=1;i<=n;i++)
	{
		int b;
		scanf("%d",&b);   
		if(b)  
		{
			sum[i]+=1;  
			sum[(i%n)+1]+=1;  
			sum[(i+n-2)%n+1]+=1;   
		}
	}
	sort(sum+1,sum+n+1); 
	ans += (n - a)*3;  
	for(int i=n;i>=n-a+1;i--) ans += sum[i];  
	printf("%d",ans); 
	return 0;  
} 
```

---

## 作者：ilibilib (赞：0)

**贪心**思想。

统计出每个位置旁有几个教授吃辣。

从大到小排序，将吃辣多的位置摆上辣菜。

剩余位置摆上不辣菜即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read() {int x=0;char ch=getchar();while(ch<'0'||ch>'9') ch=getchar();while(ch>='0'&&ch<='9') x=10*x+ch-48,ch=getchar();return x;}
bool bl[300005];
int la[300005];
bool mcmp(const int &a,const int &b) {return a>b;}
int main()
{
	int n,a,ans=0;
	n=read(),a=read();
	for(int i=1;i<=n;++i) bl[i]=read();
	la[1]=bl[n]+bl[1]+bl[2];
	for(int i=2;i<n;++i) la[i]=bl[i-1]+bl[i]+bl[i+1];
	la[n]=bl[1]+bl[n]+bl[n-1];//统计出每个位置旁有几个教授吃辣
	sort(la+1,la+n+1,mcmp);//排序
	for(int i=1;i<=a;++i) ans+=la[i];//贪心处理辣菜
	ans+=(n-a)*3;//处理不辣菜
	printf("%d",ans);
	return 0;
}
```

---

## 作者：SL789 (赞：0)

# P9728 Dining Professors题解
## 前言
[题目传送门](https://www.luogu.com.cn/problem/P9728)

比赛时第一道做出来的题，挺简单的一道贪心，先看一下题意。

## 题意简述
$n$ 个人围成一圈，每个人面前有一道菜，其中有 $a$ 道辣菜，每个人都有一个数字代表状态，1 代表可以吃辣，0 代表不能吃辣，每个人都只能吃到面前的，左边一个人的，右边一个人的菜。能吃辣的人的得分恒等于 3 分（辣与不辣都能吃也就是能吃到的三道菜都得分），而不能吃辣的人的得分等于可吃到的不辣的菜的数量，求最高的分数和。

## 分析
由题意可得，得分的高低只与不能吃辣的人有关，也就是不能吃辣的人可吃到的辣菜的总和最小时，分数和最大。

不妨从菜的角度分析，对于每一道辣菜，只影响该位置及相邻的不能吃辣的人的分数。对于每一道菜，只要取到该菜的最优解，就能保证整体取到最优解，考虑使用贪心。

- 先预处理数据，统计每个位置上的菜能影响到的位置中不能吃辣的人的数量，记录在数组中。

- 然后对数组进行升序排序,数组前 $a$ 个位置的数值的和便是影响的最小值，记为 $minl$。

- 最后计算 $ans=n\times3-minl$ 并输出。

## 代码
最后贴上 AC 代码：

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,a,ans,sta[N],num[N];
int main(){
	cin>>n>>a;
	ans=3*n;//赋初值
	for(int i=1;i<=n;i++) cin>>sta[i];
	sta[0]=sta[n],sta[n+1]=sta[1];
	for(int i=1;i<=n;i++){//预处理
		if(sta[i-1]==0) num[i]++;
		if(sta[i]==0) num[i]++;
		if(sta[i+1]==0) num[i]++;
	}
    sort(num+1,num+n+1);
    for(int i=1;i<=a;i++) ans-=num[i];//减去最小影响值
	cout<<ans;
	return 0;
} 
```

---

