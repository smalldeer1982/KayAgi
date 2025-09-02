# 题目信息

# Ehab Fails to Be Thanos

## 题目描述

You're given an array $ a $ of length $ 2n $ . Is it possible to reorder it in such way so that the sum of the first $ n $ elements isn't equal to the sum of the last $ n $ elements?

## 说明/提示

In the first example, the first $ n $ elements have sum $ 2+1+3=6 $ while the last $ n $ elements have sum $ 1+1+2=4 $ . The sums aren't equal.

In the second example, there's no solution.

## 样例 #1

### 输入

```
3
1 2 2 1 3 1
```

### 输出

```
2 1 3 1 1 2```

## 样例 #2

### 输入

```
1
1 1
```

### 输出

```
-1```

# AI分析结果

### 题目内容
# Ehab未能成为灭霸

## 题目描述
给定一个长度为 $2n$ 的数组 $a$ 。是否有可能对其重新排序，使得前 $n$ 个元素的和不等于后 $n$ 个元素的和？

## 说明/提示
在第一个示例中，前 $n$ 个元素的和为 $2 + 1 + 3 = 6$，而后 $n$ 个元素的和为 $1 + 1 + 2 = 4$ 。这两个和不相等。

在第二个示例中，没有解决方案。

## 样例 #1
### 输入
```
3
1 2 2 1 3 1
```
### 输出
```
2 1 3 1 1 2
```

## 样例 #2
### 输入
```
1
1 1
```
### 输出
```
-1
```

### 算法分类
排序

### 综合分析与结论
这些题解主要围绕判断能否对长度为 $2n$ 的数组重排，使前后 $n$ 个元素和不相等展开。大部分题解思路是先对数组排序，若排序后前后和仍相等则无解，否则输出排序后的数组，原因是排序后能使前后部分差值尽量大，更易满足条件。少部分题解采用随机化方法或通过交换特定元素来尝试满足条件。

### 所选的题解
- **作者：_byta (赞：2)  星级：4星  关键亮点：思路清晰，直接对数组排序后判断前后和是否相等，代码简洁明了**
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100002;
int n,m,k,p,q,ans,sum,tot,cnt,a[N],b[N],c[N];
int main()
{
	cin>>n;
	for(int i=1;i<=2*n;i++)
	{
		cin>>a[i];
	}
	sort(a+1,a+2*n+1);//排序
	p=n+1;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];//sum为前n个数的和
		ans+=a[p];//ans为后n个数的和
		p++;
	}
	if(ans==sum)//如果相等，则判为无解
	{
		cout<<"-1";
	}
	else//否则输出
	{
		for(int i=1;i<=2*n;i++)
		{
			cout<<a[i]<<" ";
		}
	}
	return 0;
}
```
核心实现思想：先读入数组，对数组排序后，分别计算前后 $n$ 个元素的和，若和不相等则输出数组，否则输出 -1 。

- **作者：Fearliciz (赞：0)  星级：4星  关键亮点：思路清晰，直接通过排序判断前后和，代码逻辑简洁**
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[2001],cnt1,cnt2;
signed main()
{
	int n;
	cin>>n; n*=2;
	for(int i=1;i<=n;i++) cin>>a[i];
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		if(i<=n/2) cnt1+=a[i];
		else cnt2+=a[i];
	if(cnt1!=cnt2) for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	else cout<<"-1";
	return 0;
}
```
核心实现思想：读入数组后排序，遍历数组分别计算前后 $n$ 个元素的和，根据和是否相等输出结果。

- **作者：FP·荷兰猪 (赞：0)  星级：4星  关键亮点：思路清晰，通过排序后计算前后和差值判断是否有解，代码简洁**
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,x,y) for (ll i=x;i<=y;i++)

inline int read()
{
    char c=getchar(); int x=0, f=1;
    while(c<'0' || c>'9') {if(c=='-')f=-1; c=getchar();}
    while(c>='0' && c<='9') {x=x*10+c-'0'; c=getchar();}
    return x*f;
}

int main()
{
    int n=read();
    int a[n*2+1];
    rep(i,1,n*2)
    {
        a[i]=read();
    }
    sort(a+1,a+n*2+1);//对a数组排序
    ll cnt;
    cnt=0;
    rep(i,1,n)
    {
        cnt+=a[i];
    }
    rep(i,n+1,n*2)
    {
        cnt-=a[i];
    }//cnt是前n个数的和与后n个数的和之差
    if (cnt==0)//差为0，则输出-1
    {
        cout<<"-1"<<endl;
        return 0;
    }
    else//否则输出这个排列
    {
        rep(i,1,n)
        {
            cout<<a[i]<<" ";
        }
        rep(i,n+1,n*2)
        {
            cout<<a[i]<<" ";
        }
    }
    return 0;
}
```
核心实现思想：读入数组排序后，通过累加和累减计算前后 $n$ 个元素和的差值，根据差值判断是否有解并输出相应结果。

### 最优关键思路或技巧
通过对数组排序，使得前后 $n$ 个元素的和尽量不同，从而方便判断是否存在满足条件的重排方式。这种利用排序增加前后部分差异的思维方式是解决本题的关键。

### 可拓展之处
同类型题通常围绕数组元素的组合与和的关系展开，类似算法套路是通过排序、贪心等策略改变元素组合，以满足特定的和的条件。例如，给定数组，要求找出一种排列，使得相邻元素和满足某种规律等。

### 洛谷相似题目
- [P1031 均分纸牌](https://www.luogu.com.cn/problem/P1031)
- [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
- [P1199 三国游戏](https://www.luogu.com.cn/problem/P1199) 

---
处理用时：54.29秒