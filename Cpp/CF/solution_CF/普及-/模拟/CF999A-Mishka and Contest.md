# Mishka and Contest

## 题目描述

给出长度为 $n$ 的数列，每次只能删除右端或左端小于等于 $k$ 的数，求最多能删除几个数。

## 样例 #1

### 输入

```
8 4
4 2 3 1 5 1 6 4
```

### 输出

```
5
```

## 样例 #2

### 输入

```
5 2
3 1 2 1 3
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5 100
12 34 55 43 21
```

### 输出

```
5
```

# 题解

## 作者：Ruizll (赞：2)

本题算是双端队列的典型应用题

只需要用两个循环分别从前后判断数字是否符合题目要求（ ```n <= k```
 ），再依次退出排头或排尾，并使用变量 ans 记录即可

**注意**：要在循环中同时判断队列是否为空，不然像样例三那样的测试点会 RE ~~这也就是为什么我交了两次才过~~

# **Code:**
```cpp
#include <iostream>
#include <deque>// 双端队列头文件
using namespace std;

deque <int> dq;// deque<数据类型> 变量
int n, m;

int oj(){
	int ans = 0;
	while(dq.front() <= m && !dq.empty()){
		dq.pop_front();
		ans++;
	}//从前枚举判断数据是否符标
	while(dq.back() <= m && !dq.empty()){
		dq.pop_back();
		ans++;
	}//从后枚举判断数据是否符标
	
	return ans;
}

int main(){
	
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		dq.push_back(x);// 从后插入数据，普通队列无需加_back
	}
	cout << oj() << endl;
}
```





---

## 作者：Paris_Bentley (赞：1)

# 题目描述
在一个 N 个元素的序列中，从前后两端统计小于等于 k 的数字，遇到第一个大于 k 的数字则停止，问最后一共能删掉多少个
# 基本思路
其实很简单，只需要遍历两次队列就能找到答案。也看了题解里其他伙伴们用的方法，基本把能想到的方法都用过了。
我这里用一下 STL 来解决，也算介绍了一下基础双边队列的语法。先找到队列两端的元素，如果小于等于 k 就出队，最后统计出队元素。
##  deque 用法
  如果定义了双边队列 q

1. 队列的首尾元素分别是 q.front() 和 q.back()

2. 队列前后的出队方法也比较好记 q.pop_front() 和 q.pop_back()
  
## 代码
  
  ```cpp
  
#include <bits/stdc++.h>
using namespace std;
int n,k,ans; 
deque <int> q;
int main()
{
    scanf("%d%d",&n,&k);
    for (register int i=1;i<=n;i++)
    {
        int t; 
        scanf("%d",&t);
        q.push_back(t);
    }
    while (q.size() && q.front()<=k)
    {
        ans++;
        q.pop_front();
    }
    while (q.size() &&q.back()<=k)
    {
        ans++;
        q.pop_back();
    }
    printf("%d",ans); 
    return 0;
 } 
```


---

## 作者：sysong (赞：0)

# 题解CF999A Mishka and Contest

### 题目描述

给出一个长度为 $n$ 的数列，询问其**两端**共有多少个不大于 $k$ 的数。

（~~不知道为什么没有翻译~~）

### $Solution$

由于只是两端，我们可以考虑边输入边处理。（不需要跑两遍循环）

那么就可以略去数组，直接读入判断，对于每一个满足条件的部分，统计长度，把开始和结束部分的长度加到 `ans` 里。

在判断过程中，我们设置一个标志 `f`，初始值为 1，表示开始部分的数。

若当前数符合要求，则长度加一，否则若 `f` 为一，`ans+=l`，若 `f` 为 0，那么直接把长度清零。

最后一段长度加到 `ans` 中。

### $AC\ Code$

```c++
#include <cstdio>
#define R register
#define gc() getchar()
using namespace std;

inline int rd(){
	R int x=0;R char c=gc();//,f=1
	while(c>'9'||c<'0')c=gc();//{if(c=='-')f=-1;
	while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+(c^48),c=gc();
	return x;//*f
}															// 快读

int main(){
	R int n=rd(),k=rd(),l=0,ans=0;							// l 记录长度， ans 即为答案
	for(R int i=1,f=1;i<=n;i++){
		if(rd()<=k)++l;										// 由于这些数没有后续作用，不需要记录
		else{
            if(f)ans+=l,f=0;
            l=0;
        }
	}
	printf("%d\n",ans+l);
	return 0;
}

```





***by jsntsys***

$2020.11.23$



---

## 作者：Eason_AC (赞：0)

## Content
能力值为 $k$ 的小 M 参加一次考试，考试一共有 $n$ 道题目，每道题目的难度为 $a_i$。小 M 会选择两头中的一道难度不超过他的能力值题目去做，每做完一道，这道题目会在题单中消失，序列长度减 $1$。求他按照这种方式最多能够做多少道题目。

**数据范围：$1\leqslant n,k,a_i\leqslant100$。**
## Solution
从两头开始往中间遍历，哪一头的题目难度大于 $k$，哪一头就结束扫描，得到最终能做的两头的位置 $l,r$，答案就是 $n-r+l+1$。
## Code
```cpp
int n, k, a[200007], l, r, ans;

int main() {
	getint(n), getint(k); l = 0, r = n + 1;
	_for(i, 1, n)	getint(a[i]);
	while(1) {
		if(a[l + 1] > k || l == n) break;
		++l;
	}
	while(1) {
		if(a[r - 1] > k || r - 1 == l) break;
		--r;
	}
	writeint(ans = (n - (r - l - 1)));
	return 0;
}
```

---

## 作者：ygl666666 (赞：0)

这题题目没翻译，可以看[这儿](https://www.luogu.com.cn/discuss/show/48675)。
## 思路
竟然是左边右边都要看，所以要有两次循环，只要小于等于k，就加起来。不过还没完，最后的一个判断是重点，前面一次循环得到的ansa，和后面循环得到的ansb，如果加起来大于了数的个数n，所以最多就只能是n了，但如果小些，就可以输出他们的和了。
## Code
```
/**/
#include<bits/stdc++.h>
using namespace std;
int n,k,a[10001],ansa,ansb; 
int main(){
	ios::sync_with_stdio(false);
	cin>>n>>k;
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	for(int i=0;i<n;i++){//第一次循环
		if(a[i]<=k){
			ansa++;
		}else{
			break;
		} 
	}
	for(int i=n-1;i>=0;i--){//第二次
		if(a[i]<=k){
			ansb++;
		}else{
			break;
		} 
	}
   //重点在后面的判断
	if(ansa+ansb>=n){
		cout<<n;
		return 0; 
	}else{
		cout<<ansa+ansb;
	}
	return 0;
}

```


---

## 作者：LJB00125 (赞：0)

## 大致思路
使用变量l,r来模拟现在左边取到哪里了,右边取到哪里了(初始值:l=1,r=n)

如果a[l]满足，那么ans++,l++ (取掉这一个)

如果a[r]满足，那么ans++,r-- (取掉这一个)


** 另外，需要注意的是，当n为奇数，很可能会多数一个。例子：样例3 **
```cpp
5 100
12 34 55 43 21

5
```

当l=r=3的时候,a[l]和a[r],都满足了,所以ans会+2，但实际上只能加一。(a[l]=a[r]=55<100) 这里需要一个特判。特判代码如下：

```cpp
int bfl=l,bfr=r,flag=0;
......
if(bfl==bfr&&flag==2)
{
	ans--;
	break;
}
```

其中，bfl,bfr分别是l、r的备份，flag表示加了几次。如果bfl=bfr并且是符合条件的，ans需要-1(然后就可以直接break了）

## code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,a[1005],l=1,r,ans=0; 
int main()
{
	scanf("%d %d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	r=n;
	while(l<=r)
	{
		int bfl=l,bfr=r,flag=0;
		if(a[l]<=k) ans++,l++,flag++;
		if(a[r]<=k) ans++,r--,flag++;
		if(a[l]>k&&a[r]>k) break;//两边都不行，直接退出，否则会死循环(样例2)
		if(bfl==bfr&&flag==2)//特判(样例3)
		{
			ans--;
			break;
		}
			
	}
	printf("%d",ans);
    return 0;
}
```

---

## 作者：Xxzxx (赞：0)

```
#include<iostream>
using namespace std;
int n,s,a[150],ans=0;
int main()
{
    cin>>n>>s;
    for(int i=0;i<n;i++)
        cin>>a[i];
    for(int j=n-1;j>=0;j--)
        if(s>=a[j])
        {
            ans++;//计数器++
            a[j]=2147483647;//如果不加的话，接下来的搜索可能会重复搜。
        }
        else
            break;
    for(int u=0;u<=n;u++)
    {
        if(s>=a[u])
            ans++;
        else
        {
            cout<<ans<<endl;
            return 0; 
        }
    }
    cout<<ans<<endl;
    return 0;       
} 
```

---

