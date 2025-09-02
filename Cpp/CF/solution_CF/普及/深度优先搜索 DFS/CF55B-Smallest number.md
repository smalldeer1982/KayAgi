# Smallest number

## 题目描述

Recently, Vladimir got bad mark in algebra again. To avoid such unpleasant events in future he decided to train his arithmetic skills. He wrote four integer numbers $ a $ , $ b $ , $ c $ , $ d $ on the blackboard. During each of the next three minutes he took two numbers from the blackboard (not necessarily adjacent) and replaced them with their sum or their product. In the end he got one number. Unfortunately, due to the awful memory he forgot that number, but he remembers four original numbers, sequence of the operations and his surprise because of the very small result. Help Vladimir remember the forgotten number: find the smallest number that can be obtained from the original numbers by the given sequence of operations.

## 样例 #1

### 输入

```
1 1 1 1
+ + *
```

### 输出

```
3
```

## 样例 #2

### 输入

```
2 2 2 2
* * +
```

### 输出

```
8
```

## 样例 #3

### 输入

```
1 2 3 4
* + +
```

### 输出

```
9
```

# 题解

## 作者：Fido_Puppy (赞：20)

看到了这么多 **dfs**，本蒟蒻只能表示，我不会啊！

**Tell you the truth**，我代码一长修锅的时间可就是整个上午啊！

如何不用 **dfs** 干了这题。

# **骗！对，就是骗！**

## $\mathcal{Solution}$

天然，朴素，纯真。

相信 **srand** 和 **rand** 都用过吧。

思路已经呼之欲出辣。

就按照题目意思来，一共 **3** 次，每次随机抽取 **2** 个数。

不能慌，$10^5$ 次，还凑不到最优解？

当然本题解不能保证一次性 $\mathcal{AC}$。

## $\mathcal{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[5],d[5],ans=1e16;
char c[4];
bool b[5];
inline ll math(ll x,ll y,char c) {
	if (c=='+') return x+y;
		else return x*y;
}
inline void SA() {
	ll t1,t2;
	for(ll i=1;i<=4;i++) d[i]=a[i],b[i]=true;
	for(ll i=1;i<=3;i++) {
		do {
			t1=rand()%4+1;
			t2=rand()%4+1;
		}while (!(t1!=t2&&b[t1]&&b[t2]));
		d[t1]=math(d[t1],d[t2],c[i]);
		b[t2]=false;
	}
	for(ll i=1;i<=4;i++) if (b[i]) ans=min(ans,d[i]);
}
int main() {
	srand(time(NULL));
	for(ll i=1;i<=4;i++) cin>>a[i];
	for(ll i=1;i<=3;i++) cin>>c[i];
	for(ll i=1;i<=100000;i++) SA();
	cout<<ans<<endl;
	return 0;
}
```

完结撒花！

---

## 作者：linyinuo2008 (赞：13)

好久没写搜索了，一写有点发蒙，写篇题解巩固一下。

# 1、题目分析

这题一看数据这么小，就四个数，就直接选定方法：暴搜！

但是搜索也是有技巧的，如果滥用将会溢出。

以下时几点注意：

- 必须开$long$ $long$（数据已经超了$2 \times 10^9$）。

- 初始化时要把ans设成无限大（因此第7个点爆了好几次）。

- 搜索时要用vis数组记录操作情况，搜索完要还原。

- 注意回溯条件。


# 2、搜索方法

先枚举两个要操作的数，按照当前操作符进行操作（注意：**操作符必须按顺序进行加减**），把一个数加或乘到另一个数上。

我们每次还必须拿一个present变量来记录当前要操作的数，以便搜索完后还原。

详见注释代码。

# 3、代码

贴上代码：

```cpp
#include <iostream>
using namespace std;
long long a[5],ans=0x7fffffffff;
//初始化ans无限大
char ope[4];//记录操作字符
bool vis[5];//状态数组
void dfs(int cur)
{
	int i,j;
	if(cur==3)//回溯条件明确
	{
		for(i=0;i<4;i++)
			if(!vis[i])
				ans=min(ans,a[i]);//没有被记录的数就是最终结果，求最小
		return ;//回溯
	}
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(i==j||vis[i]||vis[j])   continue;
            //若为同一个数或已被选用，跳过
			long long p=a[i];
			vis[j]=1;
			if(ope[cur]=='+')
				a[i]+=a[j];
			else if(ope[cur]=='*')
				a[i]*=a[j];
			dfs(cur+1);
			vis[j]=0;
			a[i]=p;//还原
		}
	}
}
int main()
{
	int i;
	for(i=0;i<4;i++)   cin>>a[i];
	for(i=0;i<3;i++)   cin>>ope[i];//输入
	dfs(0);
	cout<<ans;
	return 0;
}
```
管理员大大求通过！

## 若有错误，欢迎指出！


---

## 作者：爱嘤撕毯 (赞：7)

这道题第一眼看，，深搜？？还不如用全排列。。~~虽然用搜索找了全排列~~     
因为整数永远只有4个，所以我们可以以4的全排列作为运算的顺序，算完后取最小值。  
```cpp
void dfs(int k){//生成4的全排列，并把它们储存起来
	if(k>4){
		for(int i=1;i<=4;i++)
			qp[cnt][i]=n[i];
		cnt++;
		return;
	}
	for(int i=1;i<=4;i++){
		if(f[i])
			continue;
		f[i]=true;
		n[k]=i;
		dfs(k+1);
		f[i]=false;
	}
}
```
看到楼上有个大佬直接把全排列打进去了，小蒟蒻没有手，所以写了个函数生成     


------------
接下来是拿来计算的函数 （由于我太懒就写了两个几乎一样的函数  
```cpp
void js(long long n,char c,long long m){//无返回值
	if(c=='+')
		now=n+m;
	else
		now=n*m;
}
long long jss(long long n,char c,long long m){//有返回值
	if(c=='+')
		return n+m;
	else
		return n*m;
}
```
最后主函数大概会长成这样：
```cpp
int main(){
	scanf("%lld%lld%lld%lld\n",&num[1],&num[2],&num[3],&num[4]);
	scanf("%c %c %c",&x[1],&x[2],&x[3]);
	dfs(1);
	ans=1E12;
	for(int i=1;i<=24;i++){
		now=0;
		js(num[qp[i][1]],x[1],num[qp[i][2]]);
		js(now,x[2],num[qp[i][3]]);
		js(now,x[3],num[qp[i][4]]);
		ans=min(ans,now);
	}
	printf("%lld",ans);
}
```
交去评测，第二个点就WA掉了   
是因为我们漏掉了一种情况：    
![情况](https://cdn.luogu.com.cn/upload/image_hosting/w5fi0ric.png?x-oss-process=image/resize,m_lfit,h_170,w_225)    
先将第一和第二个进行计算，再将第三第四个输进行计算最后把两个结果进行计算，而全排列是不能进行这种计算的，所以我们要稍微对循环计算的部分进行一些修改
```cpp
int main(){
	scanf("%lld%lld%lld%lld\n",&num[1],&num[2],&num[3],&num[4]);
	scanf("%c %c %c",&x[1],&x[2],&x[3]);
	dfs(1);
	ans=1E12;
	for(int i=1;i<=24;i++){
		now=0;
		js(num[qp[i][1]],x[1],num[qp[i][2]]);
		long long nn;
		nn=jss(num[qp[i][3]],x[2],num[qp[i][4]]);
		minn=jss(now,x[3],nn);
		js(now,x[2],num[qp[i][3]]);
		js(now,x[3],num[qp[i][4]]);
		minn=min(minn,now);
		ans=min(ans,minn);
	}
	printf("%lld",ans);
}
```
这把每个全排列分成两种情况，按顺序计算和分成两批计算，最后就可以得到答案。   
AC代码：
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
char x[4];
long long qp[30][5],cnt=1,n[5],num[5];
bool f[5];
void dfs(int k){//全排列
	if(k>4){//达到4就记录
		for(int i=1;i<=4;i++)
			qp[cnt][i]=n[i];//记录
		cnt++;//数量加一
		return;
	}
	for(int i=1;i<=4;i++){//枚举
		if(f[i])//如果已经使用过就跳过
			continue;
		f[i]=true;//标记已使用
		n[k]=i;
		dfs(k+1);//继续
		f[i]=false;//回溯
	}
}
long long minn,ans,now;
void js(long long n,char c,long long m){//计算
	if(c=='+')
		now=n+m;
	else
		now=n*m;
}
long long jss(long long n,char c,long long m){//计算
	if(c=='+')
		return n+m;
	else
		return n*m;
}
int main(){
	scanf("%lld%lld%lld%lld\n",&num[1],&num[2],&num[3],&num[4]);//输入数字
	scanf("%c %c %c",&x[1],&x[2],&x[3]);//输入符号
	dfs(1);//计算全排列
	ans=1E12;//ans最大
	for(int i=1;i<=24;i++){
		now=0;//now清零
		js(num[qp[i][1]],x[1],num[qp[i][2]]);//计算1,2
		//printf("%d %c ",now,x[1]);
		//printf("%c",x[1]);
		long long nn;
		nn=jss(num[qp[i][3]],x[2],num[qp[i][4]]);//计算3,4
		minn=jss(now,x[3],nn);//计算（1,2），（3,4）
		//printf("%d ",minn);
		js(now,x[2],num[qp[i][3]]);//计算（1,2），3
		js(now,x[3],num[qp[i][4]]);//计算（1,2,3），3
		//printf("%d\n",now);
		minn=min(minn,now);
		ans=min(ans,minn);//比 大 小
	}
	printf("%lld",ans);//输出最小值
   return 0;//养成好习惯
}
```
完结撒花

---

## 作者：YangXiaopei (赞：5)

## 前言:

改了一晚上，测了十多次，每次改一点，终于过了。

为了纪念，来写篇不一样的题解。

## Solution:

第一眼，这不直接贪心吗？

第二眼，喔，原来是爆搜。

第三眼，不想写爆搜，写个分类讨论吧。

用一个 $cnt$ 表示运算符中 `*` 的个数，分类讨论。

为了方便，我们令 $a_1, a_2, a_3, a_4$ 为这四个数，且操作每步可任取两数，我们默认 $a$ 已经排好了序。

- $cnt = 0$
	
    全部相加即可。

- $cnt = 1$

	- `*` 是第一个
    
    	乘法的贡献比加法大，让乘法为最小两个相乘即可。
        
   - `*` 是第二个
    
    	同上。
   
   - `*` 是第三个
    
    	由和一定差小积大可知，$ans = a_1 \times (a_2 + a_3 + a_4)$。

- $cnt = 2$

	- `+` 是第一个
    
    	由和一定差小积大可知，$ans = a_1 \times a_2 \times (a_3 + a_4)$。
        
   - `+` 是第二个
    
    	这个最为复杂，我们留最后讲。
   
   - `+` 是第三个
    
    	发现 $a_1 \times a_4 + a_2 \times a_3$ 与 $a_4 + a_1 \times a_2 \times a_3$ 均有可能为最优解，取 $\min$ 即可。

- $cnt = 3$
	
    全部相乘即可。
    
最后来讲解最难的。

可以发现，第一次的乘法可以是 $a_3 \times a_4$，可以是 $a_2 \times a_3$，可以是 $a_1 \times a_2$，这三种均有可能令答案最小。

我们那 $a_3 \times a_4$ 举例。

定义一个 $x_1 = a_3 \times a_4, x_2 = a_1, x_3 = a_2$。

我们先给 $x$ 排个序。

由和一定差小积大可知，$ans = (x_3 + x_2) \times x_1$。

最后，终于来到了代码环节。

## Code:

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int cnt, ans, a[5], x[4], y[4], z[4];
char c[4];
signed main(){
	for(int i = 1; i <= 4; i++){
		cin >> a[i];
	}
	for(int i = 1; i <= 3; i++){
		cin >> c[i];
		if(c[i] == '*'){
			cnt++;
		}
	}
	sort(a + 1, a + 5);
	if(cnt == 0){
		ans = a[1] + a[2] + a[3] + a[4];
	}
	else if(cnt == 1){
		sort(a + 1, a + 5);
		if(c[1] == '*'){
			ans = a[1] * a[2] + a[3] + a[4];
		}
		else if(c[2] == '*'){
			ans = a[3] + a[4] + a[1] * a[2];
		}
		else{
			ans = a[1] * (a[2] + a[3] + a[4]);
		}
	}
	else if(cnt == 2){
		sort(a + 1, a + 5);
		if(c[1] == '+'){
			ans = (a[4] + a[3]) * a[1] * a[2];
		}
		else if(c[2] == '+'){
			x[1] = a[1] * a[2];
			x[2] = a[3];
			x[3] = a[4];
			y[1] = a[4] * a[3];
			y[2] = a[1];
			y[3] = a[2];
			z[1] = a[2] * a[3];
			z[2] = a[1];
			z[3] = a[4];
			sort(x + 1, x + 4);
			sort(y + 1, y + 4);
			sort(z + 1, z + 4);
			ans = min({(x[3] + x[2]) * x[1], (y[3] + y[2]) * y[1], (z[3] + z[2]) * z[1]});
		}
		else{
			ans = min((a[1] * a[4]) + (a[2] * a[3]), a[4] + a[1] * a[2] * a[3]);
		}
	}
	else{
		ans = a[1] * a[2] * a[3] * a[4];
	}
	cout << ans;
	return 0;
}
```
喜欢就可以点个赞，让更多人看见。

---

## 作者：AuCloud (赞：4)

一道绝妙的搜索题

## 但是为什么止于搜索？！

搜索方案其他几篇题解已经讲的非常详细了

我来~~水~~一篇不一样的题解

------------


#### N恒等于4

再算一下，4个数的全排列——24种

好耶，能存下。

考虑给4个数字的全排列和3个数字的全排列打一张表（

然后按顺序进行计算，求最小值即可

------------
表生成器（3个数时同理）
```cpp
#include <bits/stdc++.h>
using namespace std;
bool used[10];
int ans[10];
void dfs(int deep)
{
    if(deep > 4)
    {
        cout << 0 << ", ";
        for(int i = 1; i <= 4; i++)
            cout << ans[i] << ", ";
        cout << endl;
        return;
    }
    for(int i = 1; i <= 4; i++)
    {
        if(!used[i])
        {
            ans[deep] = i;
            used[i] = 1;
            dfs(deep + 1);
            used[i] = 0;
        }
    }
}
int main()
{
    dfs(1);
    return 0;
}
```
----------

最终代码

```cpp
#include <bits/stdc++.h>
#define int long long
#define fswtql return 0;
using namespace std;
int qp[25][5] = {0, 0, 0, 0, 0,//4个数的情况表
0, 1, 2, 3, 4,
0, 1, 2, 4, 3,
0, 1, 3, 2, 4,
0, 1, 3, 4, 2,
0, 1, 4, 2, 3,
0, 1, 4, 3, 2,
0, 2, 1, 3, 4,
0, 2, 1, 4, 3,
0, 2, 3, 1, 4,
0, 2, 3, 4, 1,
0, 2, 4, 1, 3,
0, 2, 4, 3, 1,
0, 3, 1, 2, 4,
0, 3, 1, 4, 2,
0, 3, 2, 1, 4,
0, 3, 2, 4, 1,
0, 3, 4, 1, 2,
0, 3, 4, 2, 1,
0, 4, 1, 2, 3,
0, 4, 1, 3, 2,
0, 4, 2, 1, 3,
0, 4, 2, 3, 1,
0, 4, 3, 1, 2,
0, 4, 3, 2, 1};
int qp2[7][4] = { // 三个数的情况表
0, 0, 0, 0,
0, 1, 2, 3,
0, 1, 3, 2,
0, 2, 1, 3,
0, 2, 3, 1,
0, 3, 1, 2,
0, 3, 2, 1};
int a[5], b[4];
int js[4];
signed main()
{
    for(int i = 1; i <= 4; i++)
    {
        cin >> a[i];
    }
    for(int i = 1; i <= 3; i++)
    {
        char ch;
        cin >> ch;
        if(ch == '*') js[i] = 2;
        else js[i] = 1;
    }
    int ans = 0x7fffffffffffffff;
    for(int i = 1; i <= 24; i++)
    {
        if(js[1] == 1) b[1] = a[qp[i][1]] + a[qp[i][2]];
        else b[1] = a[qp[i][1]] * a[qp[i][2]];
        b[2] = a[qp[i][3]];
        b[3] = a[qp[i][4]];
        for(int j = 1; j <= 6; j++)
        {
            int z1, z2;
            if(js[2] == 1) z1 = b[qp2[j][1]] + b[qp2[j][2]];
            else z1 = b[qp2[j][1]] * b[qp2[j][2]];
            if(js[3] == 1) z2 = z1 + b[qp2[j][3]];
            else z2 = z1 * b[qp2[j][3]];
            ans = min(ans, z2);
        }
    }
    cout << ans;
    fswtql
}

```

---

## 作者：翼德天尊 (赞：4)

看到数据，$n=4$，第一个反应——**爆搜**啊！

## STEP 1 简述题意

给四个数和三个符号，每次任意选取两个数按顺序按照符号结合。最终四个数和三个符号会合成一个数。最小的结果即为答案。

## STEP 2 解题思想

我们可以考虑搜索，每次选两个数与符号结合。每选择一次，我们就将其中一个数标记，然后将两个数结合后的答案放到另一个数上。最终我们进行三次结合后，我们扫一下标记数组，现在没有被标记的那一个就是这一轮的答案了。

再谈一下回溯。我们每次搜索完下一层之后，只需要将标记数组还原，然后将改变的数组的那一项的值也还原就好。

即：

```cpp
dfs(d+1);
a[j]=s;//s为变化的那一项变化前我们提前储存的数，现在赋值回来
vis[i]=0;
```

哦对，还有，记得开 $long\ long$！（考虑 $ 10^{3^4}=10^{12}>int$）

## STEP 3 AC code

```cpp
#include<bits/stdc++.h>
#define int long long//
using namespace std;
int a[5],ans=1e12+1;
char b[4];
bool vis[5];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void dfs(int d){
	if (d==4){
		int zc=0;
		for (int i=1;i<=4;i++){
			if (!vis[i]) zc=a[i];
		}
		ans=min(ans,zc);
		return;
	}
	for (int i=1;i<=4;i++){
		if (!vis[i]){
			for (int j=i+1;j<=4;j++){
				if (!vis[j]){
					vis[i]=1;
					int s=a[j];
					if (b[d]=='+') a[j]+=a[i];
					else if (b[d]=='*') a[j]*=a[i];
					dfs(d+1);
					a[j]=s;
					vis[i]=0;
				}
			}
		}
	}
}
signed main(){
	for (int i=1;i<=4;i++) a[i]=read();
	for (int i=1;i<=3;i++){
		b[i]=getchar();
		if (b[i]!='+'&&b[i]!='-'&&b[i]!='*'&b[i]!='/') b[i]=getchar();
	}
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}

```



---

## 作者：Siyuan (赞：3)

## 本题思路：
1. 首先，此题数据很小，因此肯定是 **暴力搜索**。
2. 每次枚举两个数（不需要枚举符号，因为是按次序使用符号的），更改数值并递归；到达目标状态时更新答案。记得 **回溯**！

### 代码如下：

```
#include<iostream>
#define ll long long
#define INF 0x7f7f7f7f7f7f7f7f
using namespace std;

ll a[5],ans=INF;
char p[4];

inline void dfs(const int &left)     //left指剩下的数字个数
{
    if(left==1)     //只剩下1个数，达到目标条件
    {
        register ll s;
        for(register int i=1;i<=4;i++)
            if(a[i]!=-1){s=a[i];break;}     //每次DFS时，将使用过的数字更改为-1
        ans=(ans<s?ans:s);
        return;
    }
    for(register int i=1;i<=4;i++)     //枚举2个运算数字
        for(register int j=i+1;j<=4;j++)
        {
            register int k=4-left+1;     //根据题目描述，确定本次运算符号
            if(a[i]==-1||a[j]==-1||p[k]=='-')  continue;
            register ll x=a[i],y=a[j];     //维护当前的所有数值（所有会被更改的值）
            register char t=p[k];
            p[k]='-';  a[j]=-1;     //令使用过的符号变为'-'，使用过的数字变为-1
            if(t=='+')  a[i]=x+y;  else  a[i]=x*y;     //判断符号并计算
            dfs(left-1);
            a[i]=x;  a[j]=y;  p[k]=t;     //回溯
        }
}
int main()
{
    for(register int i=1;i<=4;i++)  cin>>a[i];
    for(register int i=1;i<=3;i++)  cin>>p[i];
    dfs(4);
    cout<<ans;
    return 0;
}
```

---

## 作者：Suuon_Kanderu (赞：2)

此题很简单，数据范围极小，是一个作为搜索的练手好题。

但是 rxz 老师教过我们，暴力要写得优雅。所以我尽力写得简洁明了一些。

梳理思路：先确定我们要搜索什么（传什么参数）。

这里，我选择此时用到第几个操作符(op 数组) 以及剩余的操作数（数组）。

枚举两个操作数 $a_i,a_j$，将运算后的结果覆盖掉 $a_i$，然后把 $a_j$ 删除，搜索之后不要忘记**回溯**，还原之前的样子。

由于我们这里需要删除操作，我直接用了 vector。

注意不要忘记开 long long，$1000^4$ 使用 int 存不下。

```
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
typedef long long ll;
char op[10];int num[10];
ll ans = 0x7fffffffffffffff;//longlong最大值
vector<ll>k;
void dfs(vector<ll> a, int now) {//此时用到第几个运算符
    if(now == 4) {
		ans = min(ans , a[0]);
		return ;
	}
        vector<int>b = a;//回溯操作
	for(int i = 0; i < a.size(); i++) {//枚举运算数
        for(int j = i + 1; j < a.size(); j++) {
            if(op[now] == '+')a[i] = a[i] + a[j];
            if(op[now] == '*')a[i] = a[i] * a[j];
            a.erase(a.begin() + j);//删除
            dfs(a , now + 1);
            
            a = b;//回溯
        }
    }
}
signed main() {
    int t;
	for(int i = 1; i <= 4; i++)scanf("%lld" , &num[i]),k.push_back(num[i]);
	for(int i = 1 ; i <= 3; i++)cin >> op[i] ;
	dfs(k , 1);

	cout << ans;
	return 0;
}
```


---

## 作者：傅思维666 (赞：1)


## 题解：

暴搜。

搜索思路要选对。

注意，它是任意两两选择，并不是每次选择、运算之后，下一次选择都必须选上一次的结果。

~~所以我的第一份代码挂了~~

正确的搜索思路应该是两两枚举、标记、还原现场。

需要注意的操作是两个数运算之后的结果要存到其中一个数里，然后把另一个数打标记。这样处理的话要比很多人用的vector啥的简单很多。

还需要注意的是还原现场的操作。不能除以0。所以代码：

```cpp
#include<cstdio>
#include<iostream>
#define int long long
using namespace std;
const int INF=1e13;
int a[5];
char s[5];
bool v[5];
int ans;
void dfs(int step)
{
    if(step==4)
    {
        for(int i=1;i<=4;i++)
            if(!v[i])
                ans=min(ans,a[i]);
        return;
    }
    for(int i=1;i<=4;i++)
    {
        if(v[i])
            continue;
        for(int j=1;j<=4;j++)
        {
            if(v[j]||j==i)
                continue;
            int ori=a[j];
            if(s[step]=='+')
            {
                v[i]=1;
                a[j]+=a[i];
                dfs(step+1);
                a[j]=ori;
                v[i]=0;
            }
            else
            {
                a[j]*=a[i];
                v[i]=1;
                dfs(step+1);
                a[j]=ori;
                v[i]=0;
            }
        }
    }
}
signed main()
{
    for(int i=1;i<=4;i++)
        cin>>a[i];
    for(int i=1;i<=3;i++)
        cin>>s[i];
    ans=INF;
    dfs(1);
    cout<<ans;
    return 0;
}
```



---

## 作者：mot1ve (赞：1)

一开始用优先队列瞎搞，结果发现不太对。。数据小的话还是暴搜最稳定。由于运算符使用的顺序是确定的，所以只需要在dfs里枚举这个运算符用于哪两个数上。新添加的数覆盖其中一个数，然后另一个数标记为 $-1$ 。这样就不用处理麻烦的删除和添加操作了。注意开long long。
```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10],ans=0x3f3f3f3f3f3f3f3f;
char b[10];
void dfs(int now)//枚举该运算符用到哪两个数上 
{
	if(now==4)
	{
		for(int i=1;i<=4;i++)
		{
			if(a[i]==-1)
			continue;
			ans=min(ans,a[i]);
		}
		return ;
	}
	for(int i=1;i<4;i++)
	{
		for(int j=i+1;j<=4;j++)
		{
			int temp1=a[i],temp2=a[j];
			if(a[i]==-1||a[j]==-1)//已经用过了 
			continue;
			if(b[now]=='+')
			a[i]+=a[j];
			else a[i]*=a[j];
			a[j]=-1;
			dfs(now+1);
			a[i]=temp1;//回溯 
			a[j]=temp2;
		}
	}
}
signed main()
{
	for(int i=1;i<=4;i++)
	{
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<=3;i++)
	{
		scanf(" %c",&b[i]);
	}
	dfs(1);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Daidly (赞：1)

暴力搜索

- 用`long long`。

- 当搜索次数小于$4$时，每一次搜索判断是加还是乘，并把用过的标记为$-1$。

- 当搜索次数等于$4$时，取最小，然后返回。

- 本质上是把情况存起来，然后判断哪一种最小。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[5],ans=1e14;
char b[4];
void dfs(int qwq){
	if(qwq==4){
		for(int i=1;i<=4;i++){
			if(a[i]>=0&&a[i]<ans)ans=a[i];
		}
	}
	for(int i=1;i<4;i++){
		for(int j=i+1;j<=4;j++){
			if(a[i]>=0&&a[j]>=0){
				long long temp=a[i],tempp=a[j];
				if(b[qwq]=='+')a[i]+=a[j];
				else a[i]*=a[j];
				a[j]=-1;dfs(qwq+1);a[i]=temp;a[j]=tempp;
			}
		}
	}
}
int main(){
	for(int i(1);i<=4;++i){
	    cin>>a[i];
	}
	for(int i(1);i<=3;++i){
		cin>>b[i];
	}dfs(1);
	cout<<ans<<endl;
	return 0;
}
```


---

