# [NEERC 2015] Generators

## 题目描述

罗曼在学习线性同余发生器——最古老，也是最广为人知的伪随机数生成算法之一。线性同余发生器（LCG）以 $x_0$ 为随机种子，生成很多非负整数 $x_i$ ,它遵循以下规则：

给定非负整数 $a,b,c\space(0≤x_0<c)$ ，
$x_{i+1} = (ax_i+b)\space mod \space c$

罗曼很好奇由不同LCG产生的序列之间的关系。特别地，他有 $n$ 个不同的LCG，含有参数 $a^{(j)}, b^{(j)}, c^{(j)}\space(1≤j≤n)$。第 $j$ 个LCG会生成一个序列 $x_i^{(j)}$ 。

他希望能从每个LCG产生的序列中挑出一个数，使他们的和最大，且不被给定的 $k$ 整除。

**格式化一点来说**，他希望找到整数 $t_j \space(t_j>0,1≤j≤n)$ ，使$s=\sum\limits_{j=1}^nx_{t_j}^{(j)}$最大，且$s\not\equiv0(mod\space k)$。

## 说明/提示

时间限制：1秒

空间限制：256MB

## 样例 #1

### 输入

```
2 3
1 1 1 6
2 4 0 5
```

### 输出

```
8
4 1
```

## 样例 #2

### 输入

```
2 2
0 7 2 8
2 5 0 6
```

### 输出

```
-1
```

# 题解

## 作者：Anins (赞：2)

## [[NEERC2015] Generators](https://www.luogu.com.cn/problem/P6979)

### 题意

有 $n$ 个序列，对于每个序列给定 $x,a,b,c$，并按照 $x=(ax+b) \bmod c$ 进行扩展，每个序列取一个数进行累加，输出对 $k$ 取模不为 $0$ 的最大累加和以及每个序列中取出的数的下标，无解输出 $-1$。

### 思路

1. 显然 $ax+b$ 是单调不减的，那么对 $c$ 取模就是周期函数，只需求出一个周期即可代表整个序列。

2. 对每个序列记录对 $k$ 取模后值不同的最大值和次大值。

3. 将每个序列最大值累加，若对 $k$ 取模不为 $0$，那么输出。

4. 否则考虑将一个最大值替换成次大值，要求前后差值最小。
- 若能替换，则替换后对 $k$ 取模一定不为 $0$，进行输出。
- 若不能替换，则意味着无解，输出 $-1$。

### 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n, mod;
ll x, a, b, c, ans;
ll vis[10005]; //存储序列元素下标
struct node {
	ll index, value; //下标和值 
}q[10005][2]; //0为最大值，1为次大值 
void Make_serial() {
	memset(vis, 0, sizeof(vis));
	for(int i=1; !vis[x]; i++) {
		vis[x]=i;
		x=(a*x+b)%c;
	}
}
void Get_max(ll i) {
	q[i][0].index=q[i][1].index=q[i][0].value=q[i][1].value=-1;
	for(int j=c-1; j>=0; j--) {
		if(!vis[j]) continue;
		if(j>=q[i][0].value) { //可以更新最大值 
			if(j%mod!=q[i][0].value%mod) q[i][1]=q[i][0]; //尝试用之前最大值替换次大值 
			q[i][0].value=j, q[i][0].index=vis[j];
		} else if(j>q[i][1].value&&j%mod!=q[i][0].value%mod) { //可以更新次大值 
			q[i][1].value=j, q[i][1].index=vis[j];
		}
		if(q[i][0].value!=-1&&q[i][1].value!=-1) break; //最大值和次大值都有了，结束 
	}
}
void Get_ans() {
	for(int i=1; i<=n; i++) ans+=q[i][0].value; //求最大值累加和 
	if(ans%mod) { //取模不为0，输出 
		cout << ans << "\n";
		for(int i=1; i<=n; i++) cout << q[i][0].index-1 << " ";
	} else {
		ll idx=0; q[0][0].value=0x7f7f7f7f7f, q[0][1].value=0;
		for(int i=1; i<=n; i++) { //找到替换后差值最小的序列编号
			if(q[i][1].value==-1) continue;
			if(q[i][0].value-q[i][1].value<q[idx][0].value-q[idx][1].value) idx=i;
		}
		if(idx==0) { //不能替换
			cout << -1;
			return;
		}
		ans=ans-q[idx][0].value+q[idx][1].value; //更新替换后的答案 
		cout << ans << "\n";
		q[idx][0]=q[idx][1]; //更新替换后的编号 
		for(int i=1; i<=n; i++) cout << q[i][0].index-1 << " ";
	}
} 
int main(){
	cin >> n >> mod;
	for(int i=1; i<=n; i++) {
		cin >> x >> a >> b >> c;
		Make_serial();
		Get_max(i);
	}
	Get_ans();
	return 0;
}
```

---

## 作者：wunaidedanjuan (赞：0)

### 题意

给定 $n$ 个序列，每个序列给定四个正整数 $x_0$，$a$，$b$，$c$，序列中 $x_i=(a\times x_{i-1}+b)\mod c$，从每个序列中选一个值，并记录它们的位置，使它们的和最大且不能被 $k$ 整除。

### 思路分析

先不管和不能被 $k$ 整除这个条件，只考虑和最大，那么每个序列都选最大值即可。

再考虑不能被 $k$ 整除，如果和能被 $k$ 整除，那么若将选其中一个序列的最大值改成选它的次大值，那么这个和就不能被 $k$ 整除。因此，我们只需要记录**每个序列的最大值和次大值及其位置**即可。

查找元素最大值和次大值时，由于序列中元素是循环出现的，所以当同一元素重复出现时，就没有必要继续查找了。

这里需要注意，当一个序列中只有最大值，没有次大值时，要将次大值取序列最大值。

### 代码呈现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+10,M=20,inf=0x3f3f3f3f3f3f,mod=1e9+7;
pair<int,int>a1[N],a2[N];//每个队列的最大值和位置，次大值和位置 
bool vis[N];//每个值是否存在 
inline void read(int &x)
{
	int d=1;
	char s=getchar();
	x=0;
	while(s<'0'||s>'9')
	{
		if(s=='-')
			d=-1;
		s=getchar();
	}
	while(s>='0'&&s<='9')
	{
		x=x*10+s-'0';
		s=getchar();  
	}
	x*=d;
	return;
}
signed main()
{
	int n,k,a,b,c,x,id,cnt=0,ans=0,sum=-1;
	read(n);
	read(k);
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));//初始化位置数组 
		read(x);
		read(a);
		read(b);
		read(c);
		vis[x]=true;
		cnt=0;
		for(int j=0;j<=c+10;j++)
		{
			if(x>a1[i].first)//更新最大值 
			{
				a2[i].first=a1[i].first;
				a2[i].second=a1[i].second;
				a1[i].first=x;
				a1[i].second=j;
			}
			else if(x>a2[i].first)//更新次大值 
			{
				a2[i].first=x;
				a2[i].second=j;
			}
			x=(a*x+b)%c;
			if(vis[x])//若开始循环就跳出 
				break;
			vis[x]=true;
			cnt++;
		}
		if(cnt==0)//如果整个数列只有最大值 
			a1[i].first=a2[i].first=x;
		ans+=a1[i].first;
	}
	if(ans%k)//最大和符合要求 
	{
		printf("%lld\n",ans);
		for(int i=1;i<=n;i++)
			printf("%lld ",a1[i].second);
	}
	else//不符合要求，寻找次大值 
	{
		for(int i=1;i<=n;i++)//寻找符合条件的最大的次大值 
			if((ans-a1[i].first+a2[i].first)%k&&ans-a1[i].first+a2[i].first>sum)
			{
				sum=ans-a1[i].first+a2[i].first;
				id=i;
			}
		if(sum==-1)//没找到符合条件的次大值 
			printf("-1");
		else
		{
			printf("%lld\n",sum);
			for(int i=1;i<=n;i++)
			{
				if(i==id)
					printf("%lld ",a2[i].second);
				else
					printf("%lld ",a1[i].second);
			}
		} 
	}
	return 0;
}
```

---

