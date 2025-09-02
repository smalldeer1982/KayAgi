# Red and Blue

## 题目描述

Monocarp had a sequence $ a $ consisting of $ n + m $ integers $ a_1, a_2, \dots, a_{n + m} $ . He painted the elements into two colors, red and blue; $ n $ elements were painted red, all other $ m $ elements were painted blue.

After painting the elements, he has written two sequences $ r_1, r_2, \dots, r_n $ and $ b_1, b_2, \dots, b_m $ . The sequence $ r $ consisted of all red elements of $ a $ in the order they appeared in $ a $ ; similarly, the sequence $ b $ consisted of all blue elements of $ a $ in the order they appeared in $ a $ as well.

Unfortunately, the original sequence was lost, and Monocarp only has the sequences $ r $ and $ b $ . He wants to restore the original sequence. In case there are multiple ways to restore it, he wants to choose a way to restore that maximizes the value of

 $ $$$f(a) = \max(0, a_1, (a_1 + a_2), (a_1 + a_2 + a_3), \dots, (a_1 + a_2 + a_3 + \dots + a_{n + m})) $ $ </p><p>Help Monocarp to calculate the maximum possible value of  $ f(a)$$$.

## 说明/提示

In the explanations for the sample test cases, red elements are marked as bold.

In the first test case, one of the possible sequences $ a $ is $ [\mathbf{6}, 2, \mathbf{-5}, 3, \mathbf{7}, \mathbf{-3}, -4] $ .

In the second test case, one of the possible sequences $ a $ is $ [10, \mathbf{1}, -3, \mathbf{1}, 2, 2] $ .

In the third test case, one of the possible sequences $ a $ is $ [\mathbf{-1}, -1, -2, -3, \mathbf{-2}, -4, -5, \mathbf{-3}, \mathbf{-4}, \mathbf{-5}] $ .

In the fourth test case, one of the possible sequences $ a $ is $ [0, \mathbf{0}] $ .

## 样例 #1

### 输入

```
4
4
6 -5 7 -3
3
2 3 -4
2
1 1
4
10 -3 2 2
5
-1 -2 -3 -4 -5
5
-1 -2 -3 -4 -5
1
0
1
0```

### 输出

```
13
13
0
0```

# 题解

## 作者：zjjws (赞：5)

可以证明：**组合得到的数列 $a$ 的最大前缀和等于 $r$ 和 $b$ 各自的最大前缀和之和** 。

采取反证法：假设上述命题不成立。

那么就是说存在一个位置 $x$，满足：

$$(\sum_{i=1}^x a_i)>r_{max}+b_{max}$$

其中 $r_{max}$ 表示题目中定义的序列权值。

由于在 $a$ 中，$r$ 和 $b$ 各自内部元素的相对顺序不变，所以我们可以将  $a$ 中前 $x$ 个元素对应到 $r$ 中前 $x_r$ 个以及 $b$ 中前 $x_b$ 个。

$$(\sum_{i=1}^{x_r}r_i)+(\sum_{i=1}^{x_b}b_i)>r_{max}+b_{max}$$

但实际上根据定义，我们有：

$$\begin{cases} r_{max}\ge\sum_{i=1}^{x_r}r_i\\ b_{max}\ge \sum_{i=1}^{x_b}b_i\end{cases}$$

与上式相矛盾，故原命题成立。

那么只要两个数组分别求一次最大前缀即可。

```cpp
inline void work()
{
    int n=rin();
    LL sum=0;
    LL s=0;
    LL maxs=0;
    for(int i=1;i<=n;i++)
    {
        s+=rin();
        if(s>maxs)maxs=s;
    }
    sum+=maxs;
    n=rin();
    s=maxs=0;
    for(int i=1;i<=n;i++)
    {
        s+=rin();
        if(s>maxs)maxs=s;
    }
    sum+=maxs;
    printf("%lld\n",sum);
    return;
}
```

---

## 作者：lianchanghua (赞：3)

### 题目大意

把两个序列按顺序合并成一个新序列，求出这个新序列前缀和的最大值。

### 分析

因为“原来同组内的元素相对顺序不变。”，也就是说原来的前缀和放在新的数组里的前缀和的值依旧不变，所以组合之后数组的前缀和就是 $r$ 和 $b$ 各自的最大的前缀和相加。

这不就变成一道水的不能再水的**求和大水题**了吗？

那我们立刻就可以写出代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main(){
	ios::sync_with_stdio(false);
    int T;
    cin>>T;
    while(T--){
        int n,m;
        cin>>n;
        int sa=0,sb=0;
        int maxa=0,maxb=0;
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            sa+=a;
            maxa=max(maxa,sa);
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int b;
            cin>>b;
            sb+=b;
            maxb=max(maxb,sb);
        }
        cout<<maxa+maxb<<"\n";
    }
    return 0;
}
```

---

## 作者：I_like_magic (赞：3)

这道题其实并不难。

题目大意是这样的：已知两个序列 $r$ 和 $b$，求出合并后的最大前缀和。

很好发现：答案就是 $r$ 和 $b$ 各自的最大前缀和之和。

但要注意：$r$ 和 $b$ 可以什么都不取，因此 $maxa$ 和 $maxb$ 初始要赋值为 $0$。

AC Code：

```cpp
#include<iostream>
using namespace std;
int t;
int n,m;
int sa,sb;// sb 只是巧合
int main(){
    cin>>t;//多测
    while(t--){
        cin>>n;
        sa=0,sb=0;//初始化
        int maxa=0,maxb=0;//记得要赋值为 0
        for(int i=1;i<=n;i++){
            int a;
            cin>>a;
            sa+=a;
            maxa=max(maxa,sa);//求最大前缀和
        }
        cin>>m;
        for(int i=1;i<=m;i++){
            int b;
            cin>>b;
            sb+=b;
            maxb=max(maxb,sb);//求最大前缀和
        }
        cout<<maxa+maxb<<endl;//输出答案
    }
    return 0;// return 0 是一个好习惯
}
```

---

## 作者：Fa1thful (赞：2)

### 题意分析：
把两个序列按照原本顺序插入其中的一个序列，求出这个新序列的前缀和的最大值。
### 分析：
我们很容易想到可以把第二个序列的前缀和的最大部分插入第一个序列前缀和最大的部分就是最终的答案。所以我们可以分别给两个序列跑一个前缀和，求出最大的前缀和，再相加就是最后的结果。

![](https://cdn.luogu.com.cn/upload/image_hosting/7igryw1z.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

注：三角表示前缀和最大的位置，我们发现找到这个位置就都可以插入。

### 代码：
```cpp
# include <bits/stdc++.h>
using namespace std;
int a[10000];
int b[10000];
int pre[1000];
int pre1[1000];
int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		memset(pre, 0, sizeof(pre));
		memset(pre1, 0, sizeof(pre1));          //多组数据初始化 
		int n, m;
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}
		cin >> m;
		for (int i = 1; i <= m; i++)
		{
			cin >> b[i];
		}
		int ans = 0;
		int maxx = 0;       //第一个最大的前缀和 
		int maxn = 0;       //第二个最大的前缀和 
		for (int i = 1; i <= n; i++)
		{
			pre[i] = pre[i - 1] + a[i];              //前缀和 
			maxx = max(pre[i], maxx);        //计算最大值 
		}
		for (int i = 1; i <= m; i++)
		{
			pre1[i] = pre1[i - 1] + b[i];         //前缀和2 
			maxn = max(maxn, pre1[i]);        //计算最大值2 
		}
		cout << max(0, maxx + maxn) << endl;  //相加出结果 
	}
}
```


---

## 作者：Tenshi (赞：2)

# 前缀和

分析：因为题目不允许对两个序列进行排序，应该尽量选择两个序列中前缀和大的构成目标序列。

坑点：不要忘记0，以及只选取一个序列的情况。

代码：
```cpp
int main()
{
    int T;cin>>T;
    while(T--){
        SET0(a);SET0(b); SET0(sa);SET0(sb);
        int n,m;
        int rec1,rec2;
        
        cin>>n;
        FOR(i,1,n){
            cin>>a[i];            
        }
        sa[1]=a[1];
        FOR(i,2,n){
            sa[i]=sa[i-1]+a[i];
        }

        cin>>m;
        FOR(i,1,m){
            cin>>b[i];            
        }
        sb[1]=b[1];
        FOR(i,2,m){
            sb[i]=sb[i-1]+b[i];
        }
        cout<<max(max(0,*max_element(sb+1,sb+1+m)+*max_element(sa+1,sa+1+n)),max(*max_element(sa+1,sa+1+n),*max_element(sb+1,sb+1+m)))<<endl;
    }
	return 0;
}
```


---

## 作者：zzy_zhouzhiyuan (赞：1)

#### 题目大意
给定 $2$ 个数组，将它们合并，求合并后的最大前缀和。

#### 思路分析
我们先思考一下，两个数组合并后的最大前缀的组成是什么？很明显就是由第一个数组的最大前缀与第二个数组的最大前缀拼接得来的，因为题目中提到“原来同组内的元素相对顺序不变”。所以得出结论为：合并后数组的最大前缀和等于原来两个数组的最大前缀和相加。

注意：**求原来两个数组的最大前缀和时存最大值的变量不能赋值为无穷小，应该赋值为 $0$，因为合并后的数组的最大前缀和可以为 $0$，即可以不取任何数。**

#### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int a[105],b[105],s[105],ss[105];
int main(){
	cin>>t;
	while(t--){
		memset(s,0,sizeof(s));
		memset(ss,0,sizeof(ss));
		cin>>n;
		for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
		cin>>m;
		for(int i=1;i<=m;i++)cin>>b[i],ss[i]=ss[i-1]+b[i];
		int mx=0,mx1=0;
		for(int i=1;i<=n;i++)mx=max(mx,s[i]);
		for(int i=1;i<=m;i++)mx1=max(mx1,ss[i]);
		cout<<mx+mx1<<"\n";
	}
}
```

---

## 作者：翼德天尊 (赞：1)

这道题一个很重要的结论就是：**组合之后数组的最大前缀和就等于组合之前的两个数组的最大前缀和之和。**

这个结论是怎么推出来的呢？是题目中的一句话吸引了我的注意力：

> 原来同组内的元素相对顺序不变。

哦——？这句话告诉我们了一个信息：组合之后数组的前缀和就是组合之前的两个数组的前缀和之和。那么组合之后数组的最大前缀和显然就是组合之前的两个数组的前缀和之和喽！

求一个数组最大前缀和的代码如下：

```cpp
int get(int x[],int l){
	int ans=0,now=0;//一个记录答案，一个记录前缀和
	for (int i=1;i<=l;i++) now+=x[i],ans=max(ans,now);//取最值
	return ans;
}
```


------------


### AC code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define N 205
int t,a[N],b[N];
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
int get(int x[],int l){
	int ans=0,now=0;
	for (int i=1;i<=l;i++) now+=x[i],ans=max(ans,now);
	return ans;
}
int main(){
	t=read();
	while (t--){
		int n=read();
		for (int i=1;i<=n;i++) a[i]=read();
		int m=read();
		for (int i=1;i<=m;i++) b[i]=read();
		int ans1=get(a,n),ans2=get(b,m);
		printf("%d\n",ans1+ans2);
	}
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1469B)
## 题意
给定长度为 $n$ 和 $m$ 的两个序列，并将其合并，求最大前缀和。
## 思路
很简单，合并后最大前缀和其实就是两个序列最大前缀和之和（不用管合并的结果），可以用一个变量保存每次加上序列元素后的值，求出这个序列的最大前缀和（两个序列都进行这样的操作），随后输出两个序列最大前缀和相加的结果就可以啦。 ~~真的大水题~~
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long//不开 long long 见祖宗！（实测#1 WA ）
int n,m;
int na,nb,ma,mb;//定义
void solve(){
	cin>>n;
	for(int i=1;i<=n;i++){
	    int a;
	    cin>>a;//读入序列a
	    na+=a;
	    ma=max(ma,na);//计算序列a的最大前缀和
	}
	cin>>m;
	for(int i=1;i<=m;i++){
	    int b;
	    cin>>b;//读入序列b
	    nb+=b;
	    mb=max(mb,nb);;//计算序列b的最大前缀和
	}
	cout<<ma+mb<<endl;//输出合并后的最大前缀和
}               //注意换行！
signed main(){
    int T;
    cin>>T;
    while(T--){//T组数据
        solve();
    }
    return 0;//结束了
}
```

---

## 作者：York佑佑 (赞：0)

## 题意
把两个序列 $r,b$ 按顺序合并成一个序列，求出新序列前缀和的最大值。
## 分析
首先，两个序列合并后的最大前缀的组成就是由第一个序列的最大前缀与第二个序列的最大前缀拼接得来的。

还有一个要求是：原来同组内的元素相对顺序不变。也就是原来的前缀和放在新的数组里的前缀和的值依旧不变，所以组合之后数组的前缀和就是 $r$ 和 $b$ 各自的最大的前缀和相加。

所以本题用**求和**的方式即可做出。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t,n,m,maxa,maxb,a,b,ansa,ansb;
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>n;
		maxa=0,maxb=0,ansa=0,ansb=0;//千万别忘了初始定义 
		while(n--)
		{
			cin>>a;
			maxa=max(maxa,ansa+=a);//r序列的最大前缀和 
		}
		cin>>m;
		while(m--)
		{			
			cin>>b;
			maxb=max(maxb,ansb+=b);//b序列的最大前缀和 
		}
		cout<<maxa+maxb<<endl;//输出各自的最大前缀和相加 
	}
	return 0;
}
```


---

## 作者：lizulong (赞：0)

## 题意
求两个序列 $r$ 和 $b$，合并后的最大前缀和。
## 思路
前缀和即可，我们可以把第二个序列的前缀和的最大部分插入第一个序列前缀和最大的部分就是最终的答案。

所以我们分别给两个序列跑一个前缀和，求出最大的前缀和，再相加就是最后的结果。
## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[10000],b[10000],q1[1000],q2[1000];
signed main(){
	int t,n,m;
	cin>>t;
	while(t--){
		memset(q1, 0, sizeof(q1));
		memset(q2, 0, sizeof(q2));
		cin>>n;for(int i=1;i<=n;i++)cin>>a[i];
		cin>>m;for(int i=1;i<=m;i++) cin>>b[i];
		int ans=0,max1=0,max2=0;
		for(int i=1;i<=n;i++) {q1[i]=q1[i-1]+a[i];max1=max(q1[i],max1);}
		for(int i=1;i<=m;i++) {q2[i]=q2[i-1]+b[i];max2=max(max2,q2[i]);}
		cout<<max((int)0,max1+max2)<<endl;
	}
}
```


---

## 作者：_Gabriel_ (赞：0)

### 思路

题目就是给了两个序列 $r$ 和 $b$，把两个序列合并后求出它们的最大前缀和。

因为题目说了，原来同组内的元素相对顺序不变，意思就是原来序列的前缀和放在新的数组里的前缀和的值依旧不变，所以把两个序列合并后序列的前缀和就是 $r$ 和 $b$ 各自的最大前缀和的加和。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e2 + 10;
int a[N], b[N];

int t;

int main() {
	cin >> t;
	while (t--) {
		int max1 = 0, max2 = 0;
		int pre1 = 0, pre2 = 0;
		int n, m;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> a[i];
			pre1 += a[i];
			max1 = max(max1, pre1);
		}
		cin >> m;
		for (int i = 1; i <= m; i++) {
			cin >> b[i];
			pre2 += b[i];
			max2 = max(max2, pre2);
		}
		cout << max1 + max2 << "\n";
	}
	return 0;
}
```


---

## 作者：liukangyi (赞：0)

# 题目大意
给你 $t$ 组样例，每组样例中有一个长度为 $n$ 的数组 $r$ 与一个长度为 $m$ 的数组 $b$。现在你可以将两个数组在**不影响相对顺序**的情况下合并，即将 $b$ 数组中的每个元素按顺序穿插在 $r$ 数组的随便一个位置。最后，输出合并后的数组中从**开始位置到任意位置**总和的最大值。


------------
# 分析
根据题目，我们可知，合并后的序列中 $r$ 数组和 $b$ 数组都是按顺序出现的，而它让我们求从开始位置到任意位置的总和的话，也就是 $r$ 数组从位置 $1$ 到任意位置的总和与 $b$ 数组从位置 $1$ 到任意位置的总和加起来的值。所以，我们只需用两个数组分别记录 $r$ 数组与 $b$ 数组的前缀和，并将**两个前缀和数组各自的最大值**加起来即可。


------------
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m;
int r[110],b[110],sumr[110],sumb[110];
//定义变量 
int main(){
	cin>>t;
	while(t--){
		int maxx1=0,maxx2=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&r[i]);
			sumr[i]=sumr[i-1]+r[i]; //记录前缀和 
			maxx1=max(maxx1,sumr[i]); //统计r数组的前缀和最大值 
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++){
			scanf("%d",&b[i]);
			sumb[i]=sumb[i-1]+b[i]; //记录前缀和
			maxx2=max(maxx2,sumb[i]); //统计b数组的前缀和最大值
		}
		cout<<maxx1+maxx2<<'\n';
	}
	return 0;
} 
```


---

## 作者：scpchangyi (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1469B)

### [思路]

本题可以不用按照题意进行模拟，但是有一个重要的结论：

+ $r$ 数组的最大前缀和 $b$ 数组的最大前缀相加就能求出 $r$ 和 $b$ 合并后的最大前缀和

这是因为题目中有句话说：**原来同组内的元素相对顺序不变。**

所以我们只用求出两个数组的最大前缀和，再相加就好了。

### [代码]

```cpp
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int t,r,b,mr,mb,s1,s2,x;
int main()
{
    cin>>t;
    for(int l=1;l<=t;l++)
    	m1=0,m2=0,s1=0,s2=0;//初始化0
    	cin>>r;//r数组
    	for(int i=1;i<=r;i++){
    		cin>>x;
    		s1+=x;
    		m1=max(m1,s1);//r的最大前缀和
    	}
    	cin>>b;//b数组
    	for(int i=1;i<=b;i++){
    		cin>>x;
    		s2+=x;
    		m1=max(m1,s2);//b的最大前缀和
    	}
    	cout<<m1+m2<<"\n";//相加
    }
    return 0;
}
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF1469B)

### **[题意解析]**
让我们在序列 $r$ 和 $b$ 中分别选**连续**的一段，组成一个新的序列 $a$，使得 $a$ 的各项总和最大。

### **[思路分析]**
因为 $r_i$ 和 $b_i$ 都有可能是负数，所以和不是**递增**的。我们可以用一个变量 $s$ 来计算前 $i$ 个元素的和，分别求出序列 $r$ 和 $b$ 中最大的 $s$，相加就能求出组成的序列 $a$ 最大的各项总和了。

### **[贴上代码]**
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,r,b;
int main(){
	cin>>T;
	while(T--){
		cin>>r;
		int mxr=0,mxb=0,x,s=0;
		/*序列r中的最大s，序列b中的最大s，计算和的s*/
		for(int i=1; i<=r; i++)
			cin>>x,s+=x,mxr=max(mxr,s);
		/*让s累加，求出序列r中的最大s*/
		s=0;/*记得清0*/
		cin>>b;
		for(int i=1; i<=b; i++)
			cin>>x,s+=x,mxb=max(mxb,s);
		/*让s累加，求出序列b中的最大s*/
		cout<<mxr+mxb<<"\n";
		/*序列a最大的各项总和*/
	}
	return 0;
} 
```


---

## 作者：LXH5514 (赞：0)

## CF1469B Red and Blue

### 题目大意

感觉题面好像翻译错了，应该是前缀，必须是连续的，而翻译好像并没有强调。就是让我们求两个前缀之和最大。

### 思路

因为两个序列并没有什么关联和限制条件，因此答案就是 $r$ 的前缀 $max+l$ 的前缀 $max$。~~毕竟是道橙题~~

求前缀和应该人人都会吧，$O(n)$ 把每个前缀都处理出来，求最大的就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=100+10;
int read()
{
	int f=1;
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x*f;
}
int t;
int n,m;
int a[MAXN],b[MAXN];
int maxn1=0,maxn2=0;
int main()
{
	t=read();
	while(t--)
	{
		n=read();
		for(int i=1;i<=n;i++)
		a[i]=read();
		m=read();
		for(int i=1;i<=m;i++)
		b[i]=read();
		int sum=0;
		for(int i=1;i<=n;i++)
		sum+=a[i],maxn1=max(maxn1,sum);
		sum=0;
		for(int i=1;i<=m;i++)
		sum+=b[i],maxn2=max(maxn2,sum);
		printf("%d\n",maxn1+maxn2);
		maxn1=0;
		maxn2=0;
	}
	return 0;
}
```

 

---

