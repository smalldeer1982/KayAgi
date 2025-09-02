# Merge it!

## 题目描述

You are given an array $ a $ consisting of $ n $ integers $ a_1, a_2, \dots , a_n $ .

In one operation you can choose two elements of the array and replace them with the element equal to their sum (it does not matter where you insert the new element). For example, from the array $ [2, 1, 4] $ you can obtain the following arrays: $ [3, 4] $ , $ [1, 6] $ and $ [2, 5] $ .

Your task is to find the maximum possible number of elements divisible by $ 3 $ that are in the array after performing this operation an arbitrary (possibly, zero) number of times.

You have to answer $ t $ independent queries.

## 说明/提示

In the first query of the example you can apply the following sequence of operations to obtain $ 3 $ elements divisible by $ 3 $ : $ [3, 1, 2, 3, 1] \rightarrow [3, 3, 3, 1] $ .

In the second query you can obtain $ 3 $ elements divisible by $ 3 $ with the following sequence of operations: $ [1, 1, 1, 1, 1, 2, 2] \rightarrow [1, 1, 1, 1, 2, 3] \rightarrow [1, 1, 1, 3, 3] \rightarrow [2, 1, 3, 3] \rightarrow [3, 3, 3] $ .

## 样例 #1

### 输入

```
2
5
3 1 2 3 1
7
1 1 1 1 1 2 2
```

### 输出

```
3
3
```

# 题解

## 作者：Raych123 (赞：4)

## 思路：按模3余数分拆
#### 背景：我之前遇上一道[表面上是线段树+离散化实际上是纯模拟的最水绿题](https://www.luogu.com.cn/problem/P3740)，于是我就决定找出最水黄题~~顺便挽救一下我快消失的社区贡献~~，于是这道题成功入选了
```
在做题之前我们先要弄明白几件事

1、%运算满足分配率：如果x+y整除3，那么x%3+y%3也整除3

2、如果想要这个序列中能被3整除的元素尽可能多，那么每次合并的元素要尽可能少

所以通过这两条规律，我们可以得出：

1、序列中原有的三的倍数的元素不用改变

2、序列中模3余1和模3余2的元素要进行一次合并

3、合并后的模3余1元素或模3余2元素每三个一合并
```

是不是感觉瞬间简单了很多？

好了，直接上代码：

```
#include<cstdio>//这题不推荐用万能头，白白浪费好多空间
using namespace std;

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)//一定记住多组数据
    {
        int n,cnt[3]={};
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
        {
            int a;
            scanf("%d",&a);
            cnt[a%3]++;//数组预处理，模3余数不同的进不同的数组
        }
        if (cnt[1]>cnt[2])//如果模3余1的多就先合并完所有模3余2的，剩下模3余1的两两合并
        {
            cnt[1]-=cnt[2];
            printf("%d\n",cnt[0]+cnt[2]+cnt[1]/3);//记住不要忘了原来整除3的
        }
        else if (cnt[1]==cnt[2])//如果模3余1的和模3余2的数量一样，就不用两两合并了
        {
            printf("%d\n",cnt[0]+cnt[1]);
        }
        else if (cnt[1]<cnt[2])//如果模3余2的多就先合并完所有模3余1的，剩下模3余2的两两合并
        {
            cnt[2]-=cnt[1];
            printf("%d\n",cnt[0]+cnt[1]+cnt[2]/3);
        }
    }
    return 0;//完结撒花
}

```
### 码字不易，求求各位看官点个赞吧！

---

## 作者：fjy666 (赞：2)

## 0x01 思路
首先，我们观察到合并之后的和 $\bmod\ 3$ 只和之前两个数 $\bmod\ 3$ 有关，所以按照 $\bmod\ 3$ 余数分析。  
- $x \bmod 3 = 0$ 不要动它
- $x \bmod 3 = 1$ 先优先考虑和 $\bmod\ 3 = 2$ 的数结合，再 $3$ 个一组结合不要动它
- $x \bmod 3 = 2$ 先优先考虑和 $\bmod\ 3 = 1$ 的数结合，再 $3$ 个一组结合

而且，我们甚至都不用知道它们是什么数字，只要看 $\bmod\ 3$ 的余数就可以了。   
时间复杂度：$\Theta(n)$  
空间复杂度：$\Theta(1)$ 不用保存每个数，具体见代码。

## 0x02 代码
```cpp
#include <algorithm>
#include <cstdio>
#define _rep(i_,a_,b_) for(int i_ = a_;i_ <= b_;++i_)
typedef long long ll;
using namespace std;
int cnt[3];
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		cnt[0] = cnt[1] = cnt[2] = 0;
		int n;
		scanf("%d",&n);
		_rep(i,1,n){
			int tmp;
			scanf("%d",&tmp);
			++cnt[tmp%3];
		}
		int x = min(cnt[1],cnt[2]);
		int y = max(cnt[1],cnt[2]) - x;
		printf("%d\n",cnt[0]+x+(y/3));
	}
    return 0;
}
```

---

## 作者：A_better_world (赞：1)

题目大意：
	
   就是说有一个长度为 $n$ 的序列，你可以把序列中的任意两个数相加，然后变成新的序列。问：最多能有多少个 $3$。

注意事项：

1.相加两个数是，两个数不需要挨在一起。

2.无论把合并（就是相加）的数放在哪里都没有影响（其实这条没什么用）。

题目思路：

（$1$ 到根号 $n$）所有数的平方肯定是 $n$ 以内的完全平方数，完全立方数可以一个一个循环。一个数可能即是完全平方数，又是完全立方数，所以要去重。

然后就可以写出核心代码。
```c
for(int i=1; i<=1001; i++)
{
	if(i*i*i>n)		//超过了，后面不可能有完全立方数 。
	{
		cout<<ans<<endl;  
		break;  
	}
	else		//i*i*i是完全立方数 。
	{
		int tmp=sqrt(i*i*i)+0.00001;  
		if(tmp*tmp != i*i*i)		//i*i*i 不是完全平方数。
				ans++;  
	}
}
```
其中还有一些小细节，具体操作如下。
```c
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int t;  
	cin>>t;  
	while(t--)
	{
		int n;  
		cin>>n; 
		int ans=sqrt(n)+0.000001;		//将1到根号 n 的算上完全平方数，加0.000001是防止 double 转整数的误差。
		for(int i=1; i<=1001; i++)
		{
			if(i*i*i>n)		//超过了，后面不可能有完全立方数 。
			{
				cout<<ans<<endl;  
				break;  
			}
			else		//i*i*i是完全立方数 。
			{
				int tmp=sqrt(i*i*i)+0.00001;  
				if(tmp*tmp != i*i*i)		//i*i*i 不是完全平方数。
					ans++;  
			}
		} 
	}
	return 0;
}


```

---

## 作者：sinsop90 (赞：1)

显然这道题我们可以考虑一个贪心的政策

显然对于取模 $3$ 余 $0$ 的我们可以一个一组

对于取模 $3$ 余 $1$ 和 $2$ 的, 我们先将一个 $1$ 和一个 $2$ 分为一组

显然我们会得到 $1$ 和 $2$ 中出现个数较小的数字的个数个组

接着我们会剩下一些 $1$ 或者一些 $2$

于是我们将剩余的除以 $3$ 便可以得到剩余的可以组成多少个组

因此有了代码:

```
#include <bits/stdc++.h>
using namespace std;
int main() {
	int T, n, mps[100005], t[3];
	cin >> T;
	while(T--) {
		cin >> n;
		int ans = 0;
		memset(t, 0, sizeof(t));
		for(int i = 1;i <= n;i++) {
			cin >> mps[i];
			if(mps[i] % 3 == 0) {
				ans++;//余0的个数
			}
			else if(mps[i] % 3 == 1) {
				t[1] ++;//余1的个数
			}
			else {
				t[2] ++;//余2的个数
			}
		}
		cout << ans + min(t[1], t[2]) + (max(t[1], t[2]) - min(t[1], t[2])) / 3 << endl;
	}
}
```


---

## 作者：xukuan (赞：0)

贪心

首先，每个数的值只与它除以3的余数有关，那么我们先记下输入时对3求余值为0,1,2的各有几个，记为a\[0\],a\[1\],a\[2\]

首先a\[0\]不用管，让a\[1\]和a\[2\]尽可能多组合

最后让三个a\[1\]或a\[2\]组合

PS：开数组时只开了2位，本地Ubuntu+VScode没有错，交上去却WA了？都没有RE？

代码：

```cpp
#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#define ll long long
using namespace std;

ll t,n,a[3];

inline ll read(){
    ll x=0,tmp=1;
    char ch=getchar();
    while(!isdigit(ch)){
        if(ch=='-') tmp=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        x=(x<<3)+(x<<1)+ch-48;
        ch=getchar();
    }
    return tmp*x;
}

inline void write(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
        y=(y<<3)+(y<<1);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
}

int main(){
//    freopen("B.in","r",stdin);
//    freopen("B.out","w",stdout);
    t=read();
    while(t--){
        n=read();
        memset(a,0,sizeof(a));
        for(ll i=1; i<=n; i++) a[read()%3]++;
        ll k=min(a[1],a[2]);
        write(a[0]+k+(a[1]-k)/3+(a[2]-k)/3); putchar('\n');
    }
//    fclose(stdin); fclose(stdout);
    return 0;
}
```

---

## 作者：_HiKou_ (赞：0)

题意：在给定的数列里分组，使尽量更多的组的总和为 $3$ 的倍数。

既然只用考虑是不是 $3$ 的倍数，可以取每个数 $\text{mod }3$ 的余数，把结果分类。

- 余数为 $0$ 的不用考虑，既然要求的是三的倍数尽量多，那么直接加到答案里是最好的。
- 余数为 $1$ 的，优先选择和余数为 $2$ 的搭配。剩下的就三个一组组成三的倍数。
- 余数为 $2$ 的同理。
- 这里有一个坑点，既然要组成尽量多的三的倍数，那么如果在与 $1$ 配对完后有剩下的 $2$，就要把它们三个一组，$2+2+2=6$ 也是 $3$ 的倍数。

CODE:

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int t,i;
	scanf("%d",&t);
	while(t--)
	{
		int n,ans=0,ys[14];
		memset(ys,0,sizeof ys);//记得初始化
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			int y;
			scanf("%d",&y);
			ys[y%3]++;//分类
		}
		ans=ys[0];//余数为 0 的直接取
		int pei=min(ys[1],ys[2]);//一个 1 和一个 2 配一对，取最小值
		ans+=pei,ys[1]-=pei,ys[2]-=pei;//减去
        //剩下的三个配一对
		if(ys[1]!=0)ans+=ys[1]/3;
		if(ys[2]!=0)ans+=ys[2]/3;
		printf("%d\n",ans);
	}
	return 0;
} 
```

---

