# Sushi for Two

## 题目描述

Arkady invited Anna for a dinner to a sushi restaurant. The restaurant is a bit unusual: it offers $ n $ pieces of sushi aligned in a row, and a customer has to choose a continuous subsegment of these sushi to buy.

The pieces of sushi are of two types: either with tuna or with eel. Let's denote the type of the $ i $ -th from the left sushi as $ t_i $ , where $ t_i = 1 $ means it is with tuna, and $ t_i = 2 $ means it is with eel.

Arkady does not like tuna, Anna does not like eel. Arkady wants to choose such a continuous subsegment of sushi that it has equal number of sushi of each type and each half of the subsegment has only sushi of one type. For example, subsegment $ [2, 2, 2, 1, 1, 1] $ is valid, but subsegment $ [1, 2, 1, 2, 1, 2] $ is not, because both halves contain both types of sushi.

Find the length of the longest continuous subsegment of sushi Arkady can buy.

## 说明/提示

In the first example Arkady can choose the subsegment $ [2, 2, 1, 1] $ or the subsegment $ [1, 1, 2, 2] $ with length $ 4 $ .

In the second example there is no way but to choose one of the subsegments $ [2, 1] $ or $ [1, 2] $ with length $ 2 $ .

In the third example Arkady's best choice is the subsegment $ [1, 1, 1, 2, 2, 2] $ .

## 样例 #1

### 输入

```
7
2 2 2 1 1 2 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
6
1 2 1 2 1 2
```

### 输出

```
2
```

## 样例 #3

### 输入

```
9
2 2 1 1 1 2 2 2 2
```

### 输出

```
6
```

# 题解

## 作者：srds_cbddl (赞：5)

### 题意

给出一个只有 ```1``` 和 ```2``` 的序列，求最大连续子序列，使得该子序列的一半是 ```1```，一半是 ```2```。

### 思路

简化题意后，可得答案即为 2 个子序列中最小值的最大值。所以当 $a_i \ne a_{i + 1}$ 时，判断并更新答案即可。时间复杂度 $\mathcal{O}(n)$。

### Code

```cpp
int cnt = 1, ans = 1, minn = 0;
for (int i = 0; i < n - 1; i ++) {
    if (a[i] == a[i + 1]) cnt ++, change_max (ans, min (minn, cnt)); // "change_max (x, y);" = "x = max (x, y);"
    else minn = cnt, cnt = 1;
}
```

---

## 作者：mxxby (赞：4)

## 题目描述
给出一串长度为 $n(2 \le n \le 100000)$，只有 $1$ 和 $2$ 的序列，求出一半是 $1$，一半是 $2$ 的最长连续子串。
## 思路
~~这题简单明了，骨骼惊奇，一看就是不用数组的料。~~

 一共两种情况：

1. $a_i=a_{i-1}$ 数字与前面相同时，直接累加。
2. $a_i \ne a_{i-1}$ 数字与前面不同时，就换标记。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int n,a,y,e,k,maxs,ye;//  y--1个数，e--2个数 ye-当前为1统治还是2统治
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a);
		if(i==1) ye= (a==2) ? 2 : 1;//循环的开始时判断
		if(a==2 && ye==2) e++;//相同累加
		if(a==1 && ye==1) y++;//同理
		if(a==2 && ye==1) e=1,ye=2;//换数了，重新开始记
		if(a==1 && ye==2) y=1,ye=1;//同理
		maxs=max(maxs,min(e,y)*2);//判断这段区间1和2有几个相同
	}
	printf("%d",maxs);
	return 0;
}
```
第一篇题解，求一遍就过qwq。

---

## 作者：sz_jinzikai (赞：3)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1138A)&[CF 传送门](https://codeforces.com/problemset/problem/1138/A)
# 题目大意
给定一个只有 $1$ 和 $2$ 的数组 $a$，求出半边是 $1$，半边是 $2$，且 $1$ 和 $2$ 的数量相等的最长子串。
# 思路
因为数据**只有** $1$ 和 $2$，所以我们可以定义两个计数器，一个用于记录当前连续 $1$ 的数量，另一个则用于记录当前连续 $0$ 的数量，并且在相邻两数不等时交换作用（即原先记录 $1$ 的计数器变成记录 $2$，原先记录 $2$ 的计数器变成记录 $1$），然后取这两个计数器中较小的一个，再乘上 $2$，就得到了当前答案，然后，在这一些当前答案中取最大值就得到了最终的答案。
# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int n, a[100005], maxx, now1 = 1, now2 = 1; //定义变量
int main () { //主函数
	cin >> n; //输入 n
	for (int i = 0; i < n; i ++)
		cin >> a[i]; //输入 a
	for (int i = 1; i < n; i ++) //从第 2 个数开始循环
		if (a[i] == a[i - 1]) //如果当前值和上一个数相等
			now2 ++; //第 2 个计数器 +1
		else //如果当前值和上一个数不等
			maxx = max (maxx, min (now1, now2)), //更新最终答案
            now1 = now2, //交换两个计数器的作用
            now2 = 1; //第 2 个计数器清零
	cout << max (maxx, min (now1, now2)) * 2; //取最终的答案，并且输出答案
	return 0; //结束程序
}
```

---

## 作者：封禁用户 (赞：3)

**Flowers**

为什么这道 `Div.2 A` 的题能评黄。。。

**Hint**

可以考虑使用一种类似于 `ODT` 的思想，将所有的相同的数进行合并。

**Solution**

这道题其实很简单。

就是在 $t$ 序列中按照从前到后的顺序记录一下每一段连续并且每一个数都相同（都是 $1$ 或者 $2$）的所有的区间的长度， 然后枚举一下每两个连续的这样的区间，求这两个区间长度的最小值即可。

（描述有点不优美，请结合代码理解）

**Code**


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N],len[N];
int main(){
  int n;cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  int cnt=0,tot=0,glen=1;
  for(int i=2;i<=n;i++){
    if(a[i]!=a[i-1])len[++tot]=glen,glen=1;
    else glen++;
  }
  len[++tot]=glen;
  int result=0;
  for(int i=1;i<tot;i++)
    result=max(result,min(len[i],len[i+1]));
  cout<<result*2<<'\n';
  return 0;
}
```



---

## 作者：StudyingFather (赞：2)

我们从左往右扫描这个01串，并记录当前段的长度和前一段的长度，假如出现了一个新段的话（下一个字符和当前字符不同），我们就计算出当前的答案并更新最优解（显然，当前的答案是当前段长度和前一段长度最小值的两倍）。

这样，我们就可以在 $ O(n) $ 的时间复杂度内解决本题。

```cpp
#include <cstdio>
#include <algorithm>
using namespace std;
int a[100005];
int main()
{
 int n,ans=0;
 scanf("%d",&n);
 for(int i=1;i<=n;i++)
  scanf("%d",&a[i]);
 int cur=a[1],cnt1=0,cnt2=0;
 if(cur==1)cnt1=1;
 else cnt2=1;
 for(int i=2;i<=n;i++)
  if(a[i]!=cur)
  {
   ans=max(ans,min(cnt1,cnt2));
   if(cur==1)cnt2=1;
   else cnt1=1;
   cur=a[i];
  }
  else
  {
   if(cur==1)cnt1++;
   else cnt2++;
  }
 ans=max(ans,min(cnt1,cnt2));
 printf("%d\n",ans*2);
 return 0;
}
```


---

## 作者：Zechariah (赞：1)

巨水的题  
把相同的部分压起来给一个权值，然后求相邻两元素权值和最大就行了
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x&-x)
#define jh(x, y) x^=y^=x^=y
#define rg register
#define inl inline
typedef long long ll;
const int N = 4e5 + 5, mod = 998244353, INF = 0x3f3f3f3f;
using namespace std;
namespace fast_IO {
    inl ll read() {
        rg char c;
        rg ll x = 0;
        rg bool flag = false;
        while ((c = getchar()) == ' ' || c == '\n' || c == '\r');
        if (c == EOF)return c; if (c == '-')flag = true; else x = c ^ 48;
        while ((c = getchar()) != ' ' && c != '\n' && c != '\r'&&~c)
            x = (x << 1) + (x << 3) + (c ^ 48);
        if (flag)return -x; return x;
    }
    inl ll max(rg ll a, rg ll b) { if (a > b)return a; return b; }
    inl ll min(rg ll a, rg ll b) { if (a < b)return a; return b; }
    void write(rg ll x) { if (x < 0)putchar('-'), x = -x; if (x >= 10)write(x / 10); putchar(x % 10 ^ 48); }
}
int a[N], cnt[N];

int main(void)
{
    rg int n = fast_IO::read(), ans = 0; a[0] = -1;
    for (rg int i = 1; i <= n; ++i)
    {
        a[i] = fast_IO::read();
        if (a[i] != a[i - 1])cnt[++*cnt] = 1;
        else ++cnt[*cnt];
    }
    for (rg int i = 1; i <= *cnt; ++i)
        ans = fast_IO::max(ans, fast_IO::min(cnt[i], cnt[i + 1]) << 1);
    fast_IO::write(ans);
    return 0;
}

```


---

## 作者：qianjingzhen (赞：0)

[题目](https://www.luogu.com.cn/problem/CF1138A)

###### @zhengjh居然抄我的半成品题解，呜呜呜~~~

# 题目大意：

给出一个只有 $1$ 和 $2$ 的序列，求最大连续子序列，使得该子序列的一半是 $1$，一半是 $2$。

这是一道水题：

变量的意思：

-  $ sum1 $ 记录 $1$ 出现的个数。

-  $ sum2 $ 记录 $2$ 出现的个数。

之后分类讨论就行了（详细情况看代码）

最后别忘了把 $max1 \times 2 $ 。 

之后上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x,n,a[100001],sum1,sum2,max1=-1;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    cin>>a[1];
    if(a[1]==1){
        sum1++;
    }else{
        sum2++;
    }//特判
    for(int i=2;i<=n;i++){
        cin>>a[i];
        if(a[i]!=a[i-1]){//判断前后是否相同
            max1=max(max1,min(sum1,sum2));//记录值
            if(a[i]==1){//判断之后重新记录值
                sum1=1;
            }else{
                sum2=1;
            }
        }else{
            if(a[i]==1){//重新开始记录
                sum1++;
            }else{
                sum2++;
            }
        }
    }
    cout<<(max(max1,min(sum1,sum2))<<1);
    return 0;
}
```


---

## 作者：_rxfalty_ (赞：0)

# 题目描述
[题目传送门](https://www.luogu.com.cn/problem/CF1138A)

给出一串长度为 $n(2 \le n \le 100000)$，只有 $1$ 和 $2$ 的序列，求出一半是 $1$，一半是 $2$ 的最长连续子串。

## 思路
因为序列中只有 $1$ 和 $2$，所以可以先将一连串相同的数压缩起来得到一个值，再对压缩后的数组中相邻两个值的最小值求最大值。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000005],t[1000005],len=0,ans=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int tot=1;
	for(int i=2;i<=n+1;i++){
		if(a[i]==a[i-1]){//如果这个数和上个数相同，计数器自加 
			tot++;
		}else{//如果不同，则计数器重置为1（新的一段长度是1） 
			len++;
			t[len]=tot;
			tot=1;
		}
	}
	for(int i=1;i<=len;i++){
		ans=max(ans,min(t[i],t[i+1]));//比较ans与相邻两数最小值的最大值 
	}
	ans=ans*2;//这里别忘记*2
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题目描述

[Sushi for Two](https://www.luogu.com.cn/problem/CF1138A)

## 算法思路

定义两个变量 $cnt1$ 和 $cnt2$ 表示 $1$ 出现的次数和 $2$ 出现的次数。

然后我们分类讨论：

- 当 $a_i \ne a_{i-1}$，先记录答案，然后更新 $cnt$。

- 否则直接更新 $cnt$。

最后输出 $ans \times 2$ 就行了。（因为有 $1$ 和 $2$ 两种数）。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;//日常开long long 
const ll N=100010;
ll n,a[N],cnt1,cnt2,ans;//cnt1表示1连续出现的次数，cnt2表示2连续出现的次数，ans存答案 
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);//输入输出优化 
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
	}
	if(a[1]==1)//特判第一个点 
	{
		cnt1++;
	}
	else
	{
		cnt2++;
	}
	for(int i=2;i<=n;i++)
	{
		if(a[i]!=a[i-1])//如果和之前的数字不同 
		{
			ans=max(ans,min(cnt1,cnt2));//记录答案 
			if(a[i]==1)
			{
				cnt1=1;
			}
			else
			{
				cnt2=1;
			}
		}
		else//如果和之前的数字相同
		{
			if(a[i]==1)
			{
				cnt1++;
			}
			else
			{
				cnt2++;
			}
		}
	}
	ans=max(ans,min(cnt1,cnt2));//记录答案 
	cout<<ans*2<<"\n";//输出答案*2 
	return 0;
}
```

---

