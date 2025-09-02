# Circle of Students

## 题目描述

有 $n$ 个学生按一定的顺序围成一圈，每个学生有一个互不相同的编号 $p_i$ 。

现在这些学生围成一圈跳圆圈舞，他们可以按顺时针或逆时针跳舞，但必须满足以下条件之一：\
1、编号为 $2$ 的学生是编号为 $1$ 的学生的**顺**时针顺序的第一个学生，编号为 $3$ 的学生是编号为 $2$ 的学生的**顺**时针顺序的第一个学生，以此类推。\
2、编号为 $2$ 的学生是编号为 $1$ 的学生的**逆**时针顺序的第一个学生，编号为 $3$ 的学生是编号为 $2$ 的学生的**逆**时针顺序的第一个学生，以此类推。

例如：如果有 $5$ 个学生，按**顺**时针顺序排列的学生的 $p_i$ 为$[2,3,4,5,1]$ ，那就**顺**时针跳舞；如果有 $4$ 个学生，按**顺**时针顺序排列的学生的 $p_i$ 为$[3,2,1,4]$ ，那就**逆**时针跳舞。

一共有 $q$ 组询问。

## 说明/提示

$1\leq n,q\leq 200$\
$1\leq p_i\leq n$

## 样例 #1

### 输入

```
5
4
1 2 3 4
3
1 3 2
5
1 2 3 5 4
1
1
5
3 2 1 5 4
```

### 输出

```
YES
YES
NO
YES
YES
```

# 题解

## 作者：Dws_t7760 (赞：7)

一道简单的模拟题，建一个一维数组即可解决。

如果这些学生可以顺时针跳舞或逆时针跳舞，就输出 `YES`,否则输出 `NO`。

我们只要判断数组 $p$ 是否递增或递减就可以了。

代码如下：

```cpp
#include<iostream>
using namespace std;
int t,n,a[200];
bool shun() {
	for(int i=1;i<n;i++) if(a[i]-a[i-1]!=1&&!(a[i]==1&&a[i-1]==n)) return 0;
	return 1;
}
bool li() {
	for(int i=1;i<n;i++) if(a[i-1]-a[i]!=1&&!(a[i-1]==1&&a[i]==n)) return 0;
	return 1;
}
int main() {
	cin>>t;
	for(int i=0;i<t;i++) {
		cin>>n;
		for(int j=0;j<n;j++) cin>>a[j];
		if(shun()||li()) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}
```


---

## 作者：Luban (赞：4)

因为个人原因未能参加这次比赛，自己赛后模拟了一下~~还好没参加，不然掉rating了~~

那么言归正传，这T-A就是一个暴力模拟，算法上没啥好说的（毕竟Div2、3的T-A也就这难度）

在理解题意上，帮大家翻译两个词就可以了

clockwise 顺时针

counterclockwise 逆时针

两者满足一个即可，属于||的关系（搞的像能满足两个似的）

上代码吧：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[205];
int main()
{
	int q;
	bool flag1,flag2;
	cin>>q;
	while(q--)
	{
		memset(a,0,sizeof(a));
		int n,i=1;
		cin>>n;
		while(i<=n)
		{
			cin>>a[i];
			i++;
		}
		i=2;
		flag1=0;
		flag2=0;
		while(i<=n)
		{
			if (a[i]!=a[i-1]+1&&!(a[i]==1&&a[i-1]==n))
			{
				flag1=1;
				break;
			}
			i++;
		}
		i=2;
		while(i<=n)
		{
			if (a[i]!=a[i-1]-1&&!(a[i]==n&&a[i-1]==1))//开始没看清，打反了，就加个"!"
			{
				flag2=1;
				break;
			}
			i++;
		}
		if (flag1&&flag2)
		{
			cout<<"NO"<<endl;
		}
		else
		{
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
```
P.s:本人码风原因，代码看似较长，但压行一下压进35行应该不是问题

---

## 作者：初雪_matt (赞：2)

顺时针与逆时针其实本质一样，总会有一个分界点 $k$ 衔接左右环形区间。

考虑讨论分界点有什么特征，若分界点 $k \not= 1$ 且 $k \not= n$ 的情况下一定为 $\left|p_{k-1}-p_k\right| >1$。这是必然的，因为发现一个点与前一个点的绝对值大于 $1$ 时一定是断开了。

只要能够在环形区间内顺时针或逆时针就代表一定有一个分界点（除分界点为 $1$ 或 $n$ 的情况）。即若分界点 $k$ 的个数大于 $1$ 则不能够顺时针或逆时针，反之亦然。 

---

## 作者：andyli (赞：2)

本题可以用STL中的$list$来轻松实现，先声明两个$list$分别初始化成$1~n$和$n~1$，接下来每次将题目给出的序列循环处理，每次将序列尾部的那个数移至序列首部，判断是否与初始化的两个list相等即可。  
代码如下：  
```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <list>
#include <numeric>
using namespace std;
const int maxn = 205;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        list<int> a1, b1;
        for (int i = 1; i <= n; i++)
            a1.push_back(i), b1.push_back(i); // 初始化两个序列
        b1.reverse(); // 将第二个序列变为n~1
        list<int> li; // 输入的序列
        for (int i = 1; i <= n; i++) {
            int x;
            scanf("%d", &x);
            li.push_back(x);
        }
        if (li == a1 || li == b1)
            printf("YES\n");
        else {
            bool flag = false;
            for (int i = 1; i <= n && !flag; i++) {
                int x = li.back();
                li.pop_back();
                li.push_front(x); // 序列尾部那个数移至序列首部
                if (li == a1 || li == b1)
                    flag = true;
            }
            printf("%s\n", flag ? "YES" : "NO");
        }
    }
    return 0;
}
```

---

## 作者：_ChongYun_ (赞：1)

# 题目解析

一道纯模拟题，问你能不能顺时针或逆时针跳舞。

就是问这个数组是否递增或递减，如果满足就输出 `YES`，否则输出 `NO`。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int q,n,a[114514];
bool check(){
	bool flag1=true,flag2=true;
	for(int i=2;i<=n;i++){
		if((a[i]-a[i-1]!=1)&&!(a[i]==1&&a[i-1]==n)){
			flag1=false;
		}
	}
	for(int i=2;i<=n;i++){
		if((a[i-1]-a[i]!=1)&&!(a[i]==n&&a[i-1]==1)){
			flag2=false;
		}
	}
	return flag1||flag2; 
} 
int main(){
	cin>>q;
	while(q--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		if(check()){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}

```


---

## 作者：cff_0102 (赞：1)

可以给数组的第 $1,2$ 个数，第 $2,3$ 个数，……，第 $n-1,n$ 个数，第 $n,1$ 个数分别作差，满足条件的输入必然有 $n-1$ 个差为 $1$，$1$ 个差为 $n-1$。

不过还要特判 $n-1=1$ 的情况，也就是 $n=2$ 的情况，此时直接输出 `YES` 即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	ios::sync_with_stdio(false);
	int t;cin>>t;
	while(t--){//t 组数据 
		int n;cin>>n;
		int a[n];
		for(int i=0;i<n;i++)cin>>a[i];
		if(n==2){//特判一下
			cout<<"YES"<<endl;
			continue;
		} 
		int s1=0,sn=0;//s1 代表差中 1 的个数，sn 代表差中 n-1 的个数
		for(int i=1;i<n;i++){
			if(abs(a[i]-a[i-1])==1)s1++;
			if(abs(a[i]-a[i-1])==n-1)sn++;
		}
		if(abs(a[n-1]-a[0])==1)s1++;
		if(abs(a[n-1]-a[0])==n-1)sn++;
		if(s1==n-1&&sn==1)cout<<"YES"<<endl;//满足条件 
		else cout<<"NO"<<endl;//不满足条件 
	}
	return 0;
}
```

---

## 作者：一个低调的人 (赞：1)

- 这是道大**淼**题。

- 考虑用模拟来做。

- 题意就是判断一个环的 $p_i$ 从 $p_i$ 为1的位置开始是否满足顺时针或逆时针地由 $1$ 到 $n$ 递增。

- 我们可以直接将该环的 $p_i$ 为 $1$ 的位置，移动到第一个或最后一个位置（按顺时针或逆时针的需要来移），其他位置跟着移动。

- 移后的数列就可以直接判断相邻两个位置的 $p_i$ 的绝对值是否相差 $1$ ，若不是就直接输出 "NO" ，否则到最后输出 "YES" 。

- 具体细节详见**代码**部分

```cpp
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int t,n,a[200],tou,tp,b[200];
bool bz;
int main()
{
	scanf("%d",&t);
	while(t--) {
		scanf("%d",&n);
		for(int i=0;i<n;i++) {
			scanf("%d",&a[i]);
			if(a[i]==1)	{
				tou=i;
			}
		}
		if(tou==0) {
			if(a[n-1]==n)	{
				tp=0;
				tou=1;
			}
			else if(a[1]==n) {
				tp=n-1;
				tou=2;
			}
			else {
				printf("NO\n");
				continue;
			}
		}
		else {
			if(a[tou-1]==n) {
				tp=-tou;
				tou=1;
			}
			else if(a[(tou+1)%n]==n) {
				tp=n-1-tou;
				tou=2;
			}
			else {
				printf("NO\n");
				continue;
			}
		}
		for(int i=0;i<n;i++) b[(i+tp+n)%n]=a[i];
		bz=false;
		for(int i=0;i<n-1;i++) {
			if(abs(b[i]-b[i+1])!=1) {
				printf("NO\n");
				bz=true;
				break;
			}
		}
		if(bz==false) {
			printf("YES\n");
		}
	}
	return 0;
}
```

---

## 作者：Meatherm (赞：1)

很显然，问题可以转化为：

有一个长度为 $n$ 的数组 $a$，是 $1$~$n$ 的一个排列。问这个排列满不满足 

$$a_k=1(1\leq k \leq n),a_i+1=a_{i+1}(1 \leq i \leq k-2),a_j+1=a_{j+1}(k \leq j \leq n-1)$$

或 

$$a_k=1(1\leq k \leq n),a_i-1={a_{i+1}}(1\leq i \leq k-1),a_j-1=a_{j+1}(k+1\leq j \leq n-1)$$

满足其中一个或者全部满足输出 `YES`，否则输出 `NO`。


那么直接模拟即可。

### 代码

```
# include <bits/stdc++.h>
# define rr register
const int N=210;
int T;
int n;
int a[N];
inline bool check1(void){//判断递增
	int id;
	for(rr int i=1;i<=n;++i){
		if(a[i]==1){
			id=i;
			break;			
		}
	}
	for(rr int i=2;i<id;++i){
		if(a[i]-a[i-1]!=1){
			return false;
		}
	}
	for(rr int i=id+1;i<=n;++i){
		if(a[i]-a[i-1]!=1){
			return false;
		}
	}
	return true;
}
inline bool check2(void){//判断递减
	int id;
	for(rr int i=1;i<=n;++i){
		if(a[i]==1){
			id=i;
			break;
		}
	}
	for(rr int i=2;i<=id;++i){
		if(a[i-1]-a[i]!=1){
			return false;
		}
	}
	for(rr int i=id+2;i<=n;++i){
		if(a[i-1]-a[i]!=1){
			return false;
		}
	}
	return true;
}
int main(void){
	scanf("%d",&T);//多组数据
	while(T--){
		scanf("%d",&n);
		for(rr int i=1;i<=n;++i){
			scanf("%d",&a[i]);
		}
		if(check1()||check2()){//只要满足一个就可以
			puts("YES");
		}else{
			puts("NO");
		}
	}
	return 0;
}
```

---

## 作者：waters__god (赞：0)

## 题目思路
纯纯大模拟，甚至不能说大，只需判断数组 $a$ 是否递增或者递减即可，说成大白话就是是否一直变大或者一直变小，只要满足其中一个就行，是或的关系。
## CODE
```c++
#include<bits/stdc++.h>
using namespace std;
int p,n,a[200];
bool t1=1,t2=1;
int main()
{
	cin>>p;
	while(p--)
	{
		t1=1,t2=1;
		scanf("%d",&n);
		for(int j=0;j<n;j++) scanf("%d",&a[j]);
		for(int j=1;j<n;j++)
		{
			if(a[j]!=a[j-1]+1&&!(a[j]==1&&a[j-1]==n))
			{
				t1=0;
				break;
			}
		}
		for(int j=1;j<n;j++)
		{
			if(a[j]!=a[j-1]-1&&!(a[j]==n&&a[j-1]==1))
			{
				t2=0;
				break;
			}	
		}	
		printf((f1||f2)?"YES\n":"NO\n");
	}
}
```

---

## 作者：AstaSunch_ (赞：0)

# $\tt0x00$ 序

蒟蒻的第 $\bf\color{red}24$ 篇题解。

# $\tt0x01$ 明

有 $n$ 个学生，每个学生都有编号 $p_i$。判断他们能否顺时针跳舞或逆时针跳舞，输出 `YES` 或 `NO`。

# $\tt0x02$ 解

实际上，通过提议我们知道，想要看到他们是否能跳舞，就需要判断数列是否是递增序列或递降序列。

开一个数组，直接模拟就可以。

# $\tt0x03$ 文

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[200];
bool f1=1,f2=1;
int main() {
	cin>>t;
	while(t--){
		f1=1,f2=1;
		cin>>n;
		for(int j=0;j<n;j++) cin>>a[j];
		for(int j=1;j<n;j++) {
			if(a[j]!=a[j-1]+1&&!(a[j]==1&&a[j-1]==n)){
				f1=0;
				break;
			}
		}
		for(int j=1;j<n;j++) {
			if(a[j]!=a[j-1]-1&&!(a[j]==n&&a[j-1]==1)){
				f2=0;
				break;
			}	
		}	
		(f1||f2)?cout<<"YES\n":cout<<"NO\n";
	}
}
```


---

## 作者：xhz0311 (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1203A)

### 思路
若能够顺时针跳舞，则学生编号所构成的数列 $\{a_{n}\}$ 必须满足 $a_{i+1}=a_{i}+1(a_{i}\neq n)$。   
逆时针则有 $a_{i+1}=a_{i}-1(a_{i}\neq1)$。   
由此我们直接扫两遍序号数组即可。

### 代码
```
#include <bits/stdc++.h>
using namespace std;
int q,n,p[205];
bool flag1=1,flag2=1;
int main()
{
	scanf("%d",&q);
	while (q--)
	{
		flag1=1; flag2=1;
		scanf("%d",&n);
		for (int i=1; i<=n; i++)
		{
			scanf("%d",&p[i]);
		}
		for (int i=1; i<n; i++)
		{
			if (p[i+1]!=p[i]+1 && p[i]!=n)//顺时针
			{
				flag1=0;
				break;
			}
		}
		for (int i=1; i<n; i++)
		{
			if (p[i+1]!=p[i]-1 && p[i]!=1)//逆时针
			{
				flag2=0;
				break;
			}
		}
		if (flag1 || flag2)
		{
			printf("YES\n");
		}
		else
		{
			printf("NO\n");
		}
	}
	return 0;
}
```

---

## 作者：syhx (赞：0)

模拟题。  
输入之后开两遍循环，顺时针判断一遍，逆时针判断一遍。  
如果：当前位置的下一位递增或者和本位处于首尾位置，那么判断下一位。  
不然跳出，这个方法不行。  
有一种可以就输出 `YES`。

------------
代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int p[242];
bool pd_1(int p[],int n){//顺时针判断
	for(int i=1;i<n;i++){
		if(p[i+1]+1!=p[i]&&!(p[i]==1&&p[i+1]==n)) return 0;
		//如果不是递增或两端就跳出
	}
    return 1;
}
bool pd_2(int p[],int n){//逆时针判断
	for(int i=1;i<n;i++){
		if(p[i+1]-1!=p[i]&&!(p[i]==n&&p[i+1]==1)) return 0;
		//如果不是递增或两端就跳出
	}
    return 1;
}
void solve(){
	int n;cin>>n;
	for(int i=1;i<=n;i++) cin>>p[i];
	if(pd_1(p,n)||pd_2(p,n)) cout<<"YES\n";//有一个可以就YES
	else cout<<"NO\n";
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int q;cin>>q;
	for(int i=1;i<=q;i++) solve();
	return 0;
}
//@syhx-NaOH2009
```


---

## 作者：XBaiC (赞：0)

### 思路

模拟即可。

判断学生能否能按顺时针或逆时针取跳舞，可以的输出 `YES`，否则输出 `NO`。

时间复杂度：$\mathcal O(qn)$。

### CODE

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 1;
int a[N];
bool flag1 , flag2;
int main()
{
    int q;
    cin >> q;
    while( q-- )
    {
        int n;
        cin >> n;
        flag1 = flag2 = true;
        for( int j = 1;j <= n; j++ )
        {
            scanf( "%d" , a + j );
        }
        for( int j = 1; j < n; j++ )
        {
            if( a[j] - 1 != a[j + 1] && !( a[j] == 1 && a[j+  1]==n) )
            {
                flag1 = false;
                break;
            }
        }
        if( flag1 == true )
        {
            puts( "YES" );
            continue;
        }
        for( int j = 1; j < n; j++ )
        {
            if( a[j] + 1 != a[j + 1] && !( a[j] == n && a[j + 1] == 1 ) )
            {
                flag2 = false;
                break;
            }
        }
        if( flag2 == true )
        {
            puts( "YES" );
            continue;
        }
        puts( "NO" );
    }
    return 0;
}
```


---

## 作者：封禁用户 (赞：0)

# 题目描述

[Circle of Students](https://www.luogu.com.cn/problem/CF1203A)

# 算法思路

**模拟**

判断这些学生能否能按顺时针或逆时针跳舞即可，能的输出 YES，不能输出 NO 即可。

### 时间复杂度：$O(q \times n)$。

## 代码
```
#include<bits/stdc++.h>//万能头文件
using namespace std;
typedef long long ll;//日常开long long
const ll N=1000010;
ll q,n,a[N];
bool flag,flagflag;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化
	cin>>q;
	while(q--)
	{
		flag=flagflag=true;
		cin>>n;
		for(int j=1;j<=n;j++)
		{
			cin>>a[j];
		}
		for(int j=1;j<n;j++)//逆时针
		{
			if(a[j]-1!=a[j+1]&&!(a[j]==1&&a[j+1]==n))
			{
				flag=false;
				break;
			}
		}
		if(flag)//判断逆时针可不可以
		{
			cout<<"YES\n";
			continue;
		}
		for(int j=1;j<n;j++)//顺时针
		{
			if(a[j]+1!=a[j+1]&&!(a[j]==n&&a[j+1]==1))
			{
				flagflag=false;
				break;
			}
		}
		if(flagflag)//判断顺时针可不可以
		{
			cout<<"YES\n";
			continue;
		}
		cout<<"NO\n";//逆时针和顺时针都不可以
	}
    return 0;
}
```


---

## 作者：_colin1112_ (赞：0)

+ 这是一道简单的模拟题。

## 思路

只需判断这些学生能否能按顺时针或逆时针跳舞即可，能的输出 `YES`，不能输出 `NO` 即可。

----

AC Code：

```c++
#include <bits/stdc++.h>
#define ll long long
#define endl '\n'

using namespace std;
const int E=1e6+5;
ll q;
ll arr[E];
int main(){
	cin >>q;
	for(int i=0;i<q;i++){
		ll n;
		bool flag=1,flag1=1;
		cin >>n;
		for(int j=1;j<=n;j++){
			cin >>arr[j];
		}
		//逆时针
		for(int j=1;j<n;j++){
			if(arr[j]-1!=arr[j+1] && !(arr[j]==1 && arr[j+1]==n)){
				flag=0;
				break;
			}
		}
		if(flag){
			cout <<"YES\n";
			continue;
		}
		//顺时针 
		for(int j=1;j<n;j++){
			if(arr[j]+1!=arr[j+1] && !(arr[j]==n && arr[j+1]==1)){
				flag1=0;
				break;
			}
		}
		if(flag1){
			cout <<"YES\n";
			continue;
		}
		cout <<"NO\n";
	}
	en:
    return 0;
}
```

---

## 作者：__HHX__ (赞：0)

# 题目大意
给出循环序列 $A$ 判断从某点开始循环是否保证为**单调递增**或**单调递减**。
# 思路
此题仅需特判断 $n$ 与 $1$ 的位置与其他位置是否保证为**单调递增**或**单调递减**就可以了。

我来看一组样例：
```
5
3 2 1 5 4
```
我此时只需将序列中 $1$ 和 $5(n)$ 分开。
```
3 2 1 | 5 4
```
其中：
```
3 2 1
```
保证单调递减。

其中：
```
5 4
```
也保证单调递减。

此时我们仅需把序列一挪到序列二后面。

```
5 4 3 2 1
```
这样就变成了单调递减了。

所以我们仅需看这两个序列是否**同时满足**单调递增或单调递减。

但也要注意 $1$ 和 $n$ 除了在首尾一定要**挨着**。

不然  $1$ 到 $n$ 中的序列就连不上了。
# 代码
```cpp
#include<iostream>
using namespace std;

const int MaxN=2e2+3;
int a[MaxN];
int n;
int main(){
	int q;
	cin>>q;
	while(q--)
	{
		bool f1=0,f2=0;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<n;i++)//顺时针 
		{
			if(a[i+1]!=a[i]+1&&!(a[i]==n&&a[i+1]==1))//!(a[i]==n&&a[i+1]==1)不能翻过来，因为 1 不能为终点 n 不能为起点 
			{
				f1=1;
			}
		}
		for(int i=1;i<n;i++)//逆时针 
		{
			if(a[i+1]!=a[i]-1&&!(a[i]==1&&a[i+1]==n))//!(a[i]==n&&a[i+1]==1)不能翻过来，原因同上 
			{
				f2=1;
			}
		}
		cout<<(f1&&f2?"NO\n":"YES\n");
	}
}
```

---

## 作者：InversionShadow (赞：0)

## CF1203A Circle of Students 题解

> 话说橙题干了二十分钟。

枚举起点 $i$，去判断以 $i$ 为起点的序列 $a$ 是否满足单调递增或单调递减，**注意 $a$ 是一个环**，时间复杂度 $\mathcal{O(qn)}$。

### Code:

```cpp
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i <= y; i++)
#define frep(i, x, y) for (int i = x; i >= y; i--)

using namespace std;

const int MAXN = 201;

int q, n, a[MAXN];

bool shun() {
  bool flag, flag1;
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    flag = 1;
    for (int j = i + 1; j <= n; j++) {
      if (a[j] != a[j - 1] + 1) {
        flag = 0;
        break;
      }
      sum++; 
    }
    if (flag) {
      flag1 = 1;
      for (int j = 2; j <= n - sum - 1; j++) {
        if (a[j] != a[j - 1] + 1) {
          //cout << sum << ' ' << i << ' ' << a[j] << ' ' << a[j - 1] << endl;
          flag1 = 0;
          break;
        }
      }
      if (flag && flag1) {
        return 1;
      }
    }
  }
  return 0;
}

bool ni() {
  bool flag, flag1;
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    flag = 1;
    for (int j = i + 1; j <= n; j++) {
      if (a[j] != a[j - 1] - 1) {
        flag = 0;
        break;
      }
      sum++; 
    }
    if (flag) {
      flag1 = 1;
      for (int j = 2; j <= n - sum - 1; j++) { // 注意是环，前一个循环检查了 i + 1 ~ n，所以这个循环检查 2 ~ n - sum - 1，sum 为上个循环检查的元素数量
        if (a[j] != a[j - 1] - 1) {
          //cout << sum << ' ' << i << ' ' << a[j] << ' ' << a[j - 1] << endl;
          flag1 = 0;
          break;
        }
      }
      if (flag && flag1) {
        return 1;
      }
    }
  }
  return 0;
}

int main() {
  cin >> q;
  while (q --> 0) { // 等价 q--
    cin >> n;
    rep(i, 1, n) cin >> a[i];
    if (shun() || ni()) { //  注意是或的关系
      cout << "YES\n"; 
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}

```


---

## 作者：fls233666 (赞：0)

可以发现，这个数据范围很小：$1 \le n,q \le 200$

显然，我们可以用时间复杂度为$O(nq)$的**模拟**算法解决此问题。

题面中的跳舞的条件其实可以总结为一条：

**按顺时针或逆时针从$1$号学生往下数，如果能够输出$1$到$n$连续的编号，则可以跳舞。**

所以我们可以在读入时记录$1$号学生所在的位置，然后数数。

但是，学生们站成了一个环，而在程序中任何实现环的结构呢？

有两种办法：

1.	按题面输入顺序把学生编号存下来，从$1$号学生开始数数时，如果遇到下标超过$n$或者出现负数下标，就把下标修正回去。

2. 按题面输入顺序把学生编号存下来，把$1$号学生之前的学生复制，拼到数列前面，把$1$号学生后面的学生复制，拼到数列前面，然后开始数数。

本人按第一种方法实现，下面是代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
int num[202];
int main(){
	int test,n,g;
    bool f;
    scanf("%d",&test);
  //读入测试数据组数
    for(int ti=1;ti<=test;ti++){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%d",&num[i]);
            if(num[i]==1)
                g=i;   //找到一号学生
        }
  
  		//顺时针
        f=true;   //标记是否可以顺时针跳舞
        for(int ki=2,b=g+1;ki<=n;ki++,b++){
            if(b==n)
                b=0;  //越界修正
            if(num[b]!=ki){   //学生编号不连续
                f=false;   //不能顺时针跳舞
                break;
            }
        }
        if(f){  //可以顺时针跳舞
            printf("YES\n");
            continue;
        }
                                           
        //逆时针
        f=true;   //标记是否可以逆时针跳舞
        for(int ki=2,b=g-1;ki<=n;ki++,b--){
            if(b==-1)
                b+=n;   //负数下标修正
            if(num[b]!=ki){   //学生编号不连续
                f=false;    //不能逆时针跳舞
                break;
            }
        }
        if(f){   //可以逆时针跳舞
            printf("YES\n");
            continue;
        }
  
        printf("NO\n");  //都不行，无法跳舞
    }
	return 0;
}
```


---

## 作者：Kizuna_AI (赞：0)

由于写题解的时候hack还未完毕。有没有FST将在评论里说明   
我的博客：https://blog.likecoding.ooo  
本题解使用了is_sorted为C++11语法，若想查看C++98是怎么写的请移步其他人的题解

首先，我使用了双端队列，他可以pop_back(),pop_front(),push_back(),push_front()，且还可以下标访问，十分方便。  
然后我们每输入一个数，就将他放入双端队列的末端  
再循环n次，先查看是否是有序的，然后将最后一个数放到最前面来。如果碰到是有序的就输出`YES`，否则输出`NO`  

解释一下，为什么用了两个is_sorted  
首先，is_sorted默认是检查从小到大是否有序的，然而这道题目要求的是从小到大或者是从大到小都是可以的，所以先检查从小到大是否有序，再手写一个cmp函数，再检查从大到小是否有序。

代码：
```
#include<bits/stdc++.h>
using namespace std;
int q,n,p;
deque<int> dq,dq2;
bool cmp(const int &x,const int &y) {
	return x>y;
}
int main() {
	scanf("%d",&q);
	while(q--) {
		dq.clear();
		scanf("%d",&n);
		for(int i=1;i<=n;i++) {
			scanf("%d",&p);
			dq.push_back(p);
		}
		bool g=true;
		for(int i=1;i<=n;i++) {
			if(is_sorted(dq.begin(),dq.end())) {
				printf("YES\n");
				g=false;
				break;
			}
			if(is_sorted(dq.begin(),dq.end(),cmp)) {
				printf("YES\n");
				g=false;
				break;
			}
			p=dq.back();
			dq.pop_back();
			dq.push_front(p);
		}
		if(g) printf("NO\n");
	} 
	return 0;
}
```
Note:C++11 在NOIP中并不支持，所以尽量少用  

---

