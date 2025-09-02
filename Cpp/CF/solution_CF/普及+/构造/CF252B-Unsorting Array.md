# Unsorting Array

## 题目描述

Little Petya likes arrays of integers a lot. Recently his mother has presented him one such array consisting of $ n $ elements. Petya is now wondering whether he can swap any two distinct integers in the array so that the array got unsorted. Please note that Petya can not swap equal integers even if they are in distinct positions in the array. Also note that Petya must swap some two integers even if the original array meets all requirements.

Array $ a $ (the array elements are indexed from 1) consisting of $ n $ elements is called sorted if it meets at least one of the following two conditions:

1. $ a_{1}<=a_{2}<=...<=a_{n} $ ;
2. $ a_{1}>=a_{2}>=...>=a_{n} $ .

Help Petya find the two required positions to swap or else say that they do not exist.

## 说明/提示

In the first two samples the required pairs obviously don't exist.

In the third sample you can swap the first two elements. After that the array will look like this: 2 1 3 4. This array is unsorted.

## 样例 #1

### 输入

```
1
1
```

### 输出

```
-1
```

## 样例 #2

### 输入

```
2
1 2
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
4
1 2 3 4
```

### 输出

```
1 2
```

## 样例 #4

### 输入

```
3
1 1 1
```

### 输出

```
-1
```

# 题解

## 作者：lin_er (赞：1)

我主要想说说为什么这题看似 $O(n^3)$ 的暴力为什么能对~~首先排除测试点过水~~。  
首先每篇题解都特判的 $n\le2$ 和所有数相等的情况（原数组和排完序的两数组都相等不就是所有数都相等吗）是显然无解的,不做讨论。  
然后讨论数组中只有两种数的情况，因为在 $n\ge3$ 的时候，其有序状态比较严苛（即左侧全为一个数，右侧全为另一个数）进一步说很容易制造至少一对数对递增，一对数对递减的情况（比如将一种数放在两个另一种数之间）所以枚举出两个不同数交换合法的概率极高，所以我认为这个复杂度大概在 $O(n)$。    
然后再考虑数组中数的种类大于等于3的情况，我们假设一个各不相同的三元组 $(a,b,c)$， 显然我们有 $(a,c,b),(b,a,c),(c,b,a)$ 三种交换方式，然而有序的情况显然只有两种，显然必然存在合法解，这也说明只要枚举到两个不同的数，在第三个数的帮助下合法的概率也极高，~~至于复杂度，我也不敢说，既然能过就一定不大吧~~。  
综上，这就是为什么题解中给出的 $O(n^3)$ 的“暴力”也可以轻松过 $10^5$ 的原因，事实上他们远远跑不满便可输出合法解，看了这篇题解你也会发现无解反而更少见（都特判掉了），所以你不嫌麻烦的话，此题~~大概~~存在真正 $O(n)$ 的做法，就留给读者发挥吧~~绝不是因为懒不想写代码~~。  
那就到此为止吧！（如有错误，欢迎指正）。

---

## 作者：XXh0919 (赞：1)

这道题直接暴力就可以过。首先我们可以发现，当 $n=1$ 或者是 $n=2$ 时是绝对无解的，想想都能知道为什么。其次，若这个序列打乱之后仍和原来的序列是一样的，那也肯定是无解的。因此我们就可以暴力任何可能交换的地方并判断，如果满足既不是递增又不是递减，就直接输出，否则就输出 $-1$。

**AC Code：**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n;
int a[1000001],a2[1000001],a3[1000001];

bool cmp(long long a,long long b){
	return a>b;
}

bool g(int a[],int b[]){
	for(int i=1;i<=n;++i){
		if(a[i]!=b[i])return 0;
	}
	return 1;
}

int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		a2[i]=a[i];
		a3[i]=a[i];
	}
	sort(a2+1,a2+n+1);
	sort(a3+1,a3+n+1,cmp);//统统打乱
	if(n==1||n==2||g(a,a2)&&g(a,a3)){//特判
		cout<<-1<<endl;
		return 0;
	}
	if(n>2){
		for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
	            if(a[i]!=a[j]){
	            	swap(a[i],a[j]);
		            if(!g(a,b)&&!g(a,c)){
		                cout<<i<<' '<<j<<endl;
		                return 0;
		            }
		            swap(a[i],a[j]);
				}else continue;
            }
        }
	}
	cout<<-1<<endl;
	return 0;
}
```
注：借鉴了用户 [My_name_is_WA](https://www.luogu.com.cn/user/1004460) 的思路。

管理员求过！！！！！

---

## 作者：可持久化oier (赞：0)

**思路**：

这道题我们可以用暴力枚举，三层循环来做。这里我们需要进行一个特判，读入时特判一下，当 $n=1$ 或 $n=2$ 那么一定是无解的，直接输出 $-1$。第二种情况，就是其打乱后顺序和之前一样，也是直接输出 $-1$。如果都不存在，直接暴力枚举所有可以交换的点，如果可以，就输出其，下面是代码。

**code**：

```c
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 5;
int n;
ll tt[N], a[N], b[N], c[N];
bool check(ll *a, ll *b, int n) {
	for (int i = 1; i <= n; i++)
		if (a[i] != b[i]) return false;
	return true;
}
bool cmp(int a, int b) {
	return a > b;
}
int main() {
	scanf("%d", &n);
	if (n == 1 || n == 2) {
		printf("%d\n", -1);
		return 0;
	}
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		b[i] = a[i], c[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	sort(c + 1, c + n + 1, cmp);
	if (check(a, b, n) && check(a, c, n)) {
		printf("%d\n", -1);
		return 0;
	}
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) {
			if (a[i] == a[j]) continue;
			swap(a[i], a[j]);
			if (!check(a, b, n) && !check(a, c, n)) {
				printf("%d %d", i, j);
				return 0;
			}
			swap(a[i], a[j]);
		}
	printf("%d\n", -1);
	return 0;
}
```

---

## 作者：王逸辰 (赞：0)

# CF252B Unsorting Array 题解
~~这是我写过的最简单的绿题。~~
## 思路
根据样例就可以发现，当 $n$ 等于 $1$ 或 $2$ 时，是无解的。

双重循环枚举所有可以交换的两个数，然后再判断这个序列是否是升序或降序就可以了。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[100010],b[100010],c[100010],n;
bool pd(int a[],int b[]){
    for(int i=(1); i<=n; ++i)
        if(a[i]!=b[i])
			return false;
    return true;
}
bool cmp2(int a,int b){
    return a>b;
}
int main(){
    cin>>n;
    for(int i=(1); i<=n; ++i)
        cin>>a[i],b[i]=a[i],c[i]=a[i];
    sort(b+1,b+n+1);
    sort(c+1,c+n+1,cmp2);
    if(pd(a,b)&&pd(a,c))
        cout<<-1<<endl;
    else if(n==1||n==2)
        cout<<-1<<endl;
    else {
        for(int i=(1); i<=n; ++i)
            for(int j=(i+1); j<=n; ++j)
	            if(a[i]!=a[j]){
		            swap(a[i],a[j]);
		            if(!pd(a,b)&&!pd(a,c)){
		            	cout<<i<<" "<<j<<endl;
						return 0;
		            }
		            swap(a[i],a[j]);//如果不行就还原 
	            }
    	cout<<-1<<endl;
    }
    return 0;
}
```

---

## 作者：Sammy_prime (赞：0)

[CF252B](https://www.luogu.com.cn/problem/CF252B)

# 思路

没啥好说的，纯暴力，时间复杂度 $O(n^3)$ 如果 $n=1$ 或 $n=2$，直接输出 $-1$。如果数组打乱之后仍和原来的是一样的，直接输出 $-1$。暴力枚举所有可以能交换的地方，如果使得这个数列不呈递增或递减，就直接输出。如果都不满足，输出 $-1$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n; ll temp[N],a[N],b[N],c[N];
bool check(ll a[],ll b[],int n){
	for(ll i=1;i<=n;i++)
		if(a[i]!=b[i]) return false;
	return true;
}
bool cmp(ll a,ll b){
	return a>b;
}
int main(){
	scanf("%d",&n);
	if(n==1||n==2){
		printf("%d\n",-1);
		return 0;
	}
	for(ll i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		b[i]=a[i],c[i]=a[i];
	}
	sort(b+1,b+n+1);	sort(c+1,c+n+1,cmp);
	if(check(a,b,n)&&check(a,c,n)){
		printf("%d\n",-1);
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(a[i]==a[j]) continue;
			swap(a[i],a[j]);
			if(!check(a,b,n)&&!check(a,c,n)){
				printf("%d %d",i,j);
				return 0;
			}
			swap(a[i],a[j]);
		}
	printf("%d\n",-1);
	return 0;
}
```

---

## 作者：_int123_ (赞：0)

### 题意：

现在有 $n$ 个数，问是否可以交换两个不相同的数，使得这个数列不呈递增或递减（简单来说是没有排序），不行则输出 $-1$，可以请输出交换哪两个数所在位置。

### 思路：

1. 显然，$n=1$ 或 $n=2$ 时不行，直接输出 $-1$。

2. 我们定义 $3$ 个数组，记为 $a,b,c$，其中，$a$ 为原数组，$b$ 和 $c$ 为 $a$ 数组正序与倒序排序后的数组。这时，如果我们发现 $a,b,c$ 三个数组完全相同，也直接输出 $-1$。

3. 然后，我们暴力枚举每一对可交换的数，如果可以就直接输出。

### AC 代码：

```cpp
#include<bits/stdc++.h>//万能头文件 
#define int long long//保险起见，开 long long 
using namespace std;
int n;
int a[100005],b[100005],c[100005];
bool xt(int *x,int *y)//也可以写为 bool xt(int x[],int y[])，用来比较两个数组是否完全相同。 
{
	for(int i=1;i<=n;i++)
		if(x[i]!=y[i])
			return false;
	return true;
} 
bool nzr(int x,int y)
{
	return x>y;
}
signed main()//因为 #define int long long 了，要用 signed 
{
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);//加速 
	cin>>n;//输入 
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=c[i]=a[i];
	sort(b+1,b+n+1);//正序 
	sort(c+1,c+n+1,nzr);//倒序 
	if(n==1||n==2||xt(a,b)==true&&xt(a,c)==true)//特判 
	{
		cout<<-1;
		return 0;
	}
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(a[i]!=a[j])//不相同代表可以换 
			{
				swap(a[i],a[j]);//换一下试试看 
				if(xt(a,b)==false&&xt(a,c)==false)//如果可以，直接输出 
				{
					cout<<i<<" "<<j;
					return 0;
				}
			}
			swap(a[i],a[j]);//不行就换回来 
		}
	cout<<-1;//都不行输出 -1 
	return 0;
}
```

完结撒花！！！

---

## 作者：OIer6666 (赞：0)

求过！

暴力能过的水题。该代码时间复杂度为：$O(n^3)$。（因为测试点比较水）

解题思路：

- 判断 $n=1$ 或 $n=2$ 的情况，如果满足，输出 $-1$。
- 如果数组排序了和原来完全相同，输出 $-1$。
- 暴力任何可能交换的地方，判断。如果满足既不是递增又不是递减，输出。如果每一个情况都不满足，输出 $-1$。

# AC CODE
```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#define ll long long
#define N 100005
#define tend return 0
using namespace std;
ll temp[N];
ll a[N],up[N],down[N];
bool same(ll a[],ll b[],ll n){
	for(ll i=1;i<=n;i++){
		if(a[i]!=b[i])
			return false;
	}
	return true;
}
bool cmp(ll a,ll b){
	return a>b;
}
int main(){
	ios::sync_with_stdio(false);
	ll n;cin>>n;
	for(ll i=1;i<=n;i++){
		cin>>a[i];
		up[i]=down[i]=a[i];
	}
	stable_sort(up+1,up+n+1);
	stable_sort(down+1,down+n+1,cmp);
	if(n==1||n==2){
		cout<<-1;
		tend;
	}
	if(same(a,up,n)&&same(a,down,n)){
		cout<<-1;
		tend;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i]==a[j])
				continue;
			swap(a[i],a[j]);
			if(!same(a,up,n)&&!same(a,down,n)){
				cout<<i<<" "<<j;
				tend;
			}
			swap(a[i],a[j]);
		}
	}
	cout<<-1;
	tend;//水题完成啦
}
```

---

## 作者：liuhaopeng666 (赞：0)

我做完题之后，建议评普及$-$。

# 思路

特判 $n=1$ 和 $n=2$ 时的情况（都输出 $-1$ ）。

再进行枚举，先进行交换之后判断是否为升序或者降序，如果仍然不是的话就输出序号，然后直接结束程序，如果仍然是就换回来，继续枚举。
## Code（有注释）
```cpp
#include<iostream>
#include<algorithm>
using namespace std;
bool cmp(int a,int b){
    return a>b;
}//从大到小排序
int n;
bool pd(int a[],int b[]){//判断两个数组是否完全相同
    for(int i=1;i<=n;i++){
        if(a[i]!=b[i]) return false;
    }
    return true;
}
int main(){
    cin>>n;
    int a[100010]={0};
    int b[100010]={0};//从小到大排序
    int c[100010]={0};//从大到小排序
    for(int i=1;i<=n;i++){
        cin>>a[i];
        b[i]=a[i];
        c[i]=a[i];//复制数组
    }
    sort(b+1,b+n+1);//排序
    sort(c+1,c+n+1,cmp);//从大到小排序
    if(pd(a,b)&&pd(a,c)){
        cout<<-1<<endl;
        return 0;//直接结束
    }
    if(n==1){//如果n为1，直接输出-1（因为交换不了
        cout<<-1<<endl;
        return 0;//直接结束
    }
    if(n==2){//如果n=2
        cout<<-1<<endl;//直接输出，因为怎么交换都是升序或者降序
        return 0;//直接结束
    }  
    if(n>2){//处理其他情况
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){//枚举两个数
            if(a[i]==a[j]) continue;//如果两个数相同，没必要换
                swap(a[i],a[j]);//先交换
                if(!pd(a,b)&&!pd(a,c)){//如果数组还是无序
                    cout<<i<<" "<<j<<endl;//直接输出
                    return 0;//直接结束
                }
                swap(a[i],a[j]);//如果不选，换回来
            }
        }
    } 
    cout<<-1<<endl;//如果做不到，输出-1
    return 0;//完结撒花！！！
}
```


---

## 作者：开始新的记忆 (赞：0)

题目大意：现在有n个数，问是否可以交换两个不相同的数，使得这个数列不呈递增或递减（简单来说是没有排序），不行则输出-1，可以请输出交换哪两个数所在位置

大致思想：一看n的范围，哇靠好难啊QAQ，不能枚举，然后想了一想可以的数列有什么规律，发现输出-1的只有两种可能：n==2或者所有数都一样。因为当n==2时范围不大，可以放到最后看有没有可交换的再判。其余情况如下：在双重循环中，当i=1时，如果第k个(n>=k>2)数不能和第i个数交换，那么说明第k个数必定是最大或最小的（不然排不了序），那当k与2交换时就可以了

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],aa[100010],aaa[100010];
bool flag=0;

bool cmp(int x,int y)
{
	return x>y;
}

bool judge(int *x,int *y)
{
	for(int i=1;i<=n;++i)
	    if(x[i]!=y[i])
	        return 0;
	return 1;
}

int main()
{   cin>>n;
    for(int i=1;i<=n;++i)
	{
		cin>>a[i];
		aa[i]=a[i];aaa[i]=a[i];
	}
	sort(aa+1,aa+n+1);
	sort(aaa+1,aaa+n+1,cmp);
	if(judge(a,aa) && judge(a,aaa))
	{
		cout<<-1<<endl;
		return 0;
	}
	for(int i=1;i<=n;++i)
	{
	    for(int j=i+1;j<=n;++j)
		{
			if(a[i]==a[j])
				continue;
			swap(a[i],a[j]);
			if(!judge(a,aa) && !judge(a,aaa))
			{
				flag=1;
				cout<<i<<' '<<j<<endl;
				break;
			}
			swap(a[i],a[j]); 
		} 
	    if(flag)
	        break;
	}
	if(!flag)
	    cout<<-1<<endl;
	return 0;
}
```


---

