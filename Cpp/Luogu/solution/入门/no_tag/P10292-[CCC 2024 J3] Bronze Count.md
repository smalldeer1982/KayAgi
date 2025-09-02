# [CCC 2024 J3] Bronze Count

## 题目描述

一次比赛结束后，您可能迫切地想知道有多少参赛者获得了铜牌？

金牌会授予所有获得最高分的参赛者。银牌会授予获得第二高分的所有参赛者。铜牌会授予获得第三高分的所有参赛者。

给定一份参赛选手的成绩列表，请求出获得铜牌所需的分数以及有多少人正好得到这一分数。

![](https://cdn.luogu.com.cn/upload/image_hosting/l5gzr1cf.png)

## 说明/提示

**【样例 1 解释】**

得到铜牌需要 $62$ 分并且有一个参赛者正好得到这一分数。

**【样例 2 解释】**

得到铜牌需要 $60$ 分并且有两个参赛者正好得到这一分数。

**【数据范围】**

**本题采用捆绑测试。**

对于所有数据，保证 $1\leq N\leq 2.5\times 10^5$，分数 $s$ 满足 $0\leq s\leq 75$，至少存在三个不同的分数。

下面的表格显示了 $15$ 分的分配方案：

| 分值 | 描述 | 范围 |
| :-: | :- | :-: |
| $6$ | 分数互不相同并且参赛者数量很少。 | $N \leq 50$ |
| $7$ | 分数可能存在相同并且参赛者数量很少。 | $N \leq 50$ |
| $2$ | 分数可能存在相同并且参赛者数量可以很大。 | $N \leq 2.5 \times 10^5$ |

## 样例 #1

### 输入

```
4
70
62
58
73```

### 输出

```
62 1```

## 样例 #2

### 输入

```
8
75
70
60
70
70
60
75
70```

### 输出

```
60 2```

# 题解

## 作者：xyx404 (赞：8)

## 思路：
使用桶进行储存，然后从最大的分数从小历遍，当现在是第三个有值的，这就是铜牌，然后输出分数和人数就可以了。

## 代码：
```cpp
#include<bits/stdc++.h>
#define LL long long
#define CPPname using namespace std
CPPname;
int tong[76],n,tamp;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>tamp;
		tong[tamp]++;// 使用桶进行储存 
	}
	tamp=0;//计算是第几大的 
	for(int i=75/* 题目中保证每个分数在 75 以下 */;i>=0/* 题目中保证每个分数在 0 以上 */;i--){
		if(tong[i]!=0)tamp++;
		if(tamp==3){
			cout<<i<<" "<<tong[i];
			return 0;
		} 
	}
	return 0;
}

```

---

## 作者：封禁用户 (赞：6)

[题目传送门](https://www.luogu.com.cn/problem/P10292)

## 题意

输入一个数 $n$ 以及 $n$ 个数 $a_i$，输出**第三名的分数**以及**第三名的个数**。

## 思路

毕竟是入门题，记录一个分数出现多少次，而不用开一个数组排序。然后从满分 $75$ 开始枚举到 $0$ 分，如有人达到此分数， 记录个数 $cnt$ 加 $1$，在 $cnt$ 为 $3$ 时跳出循环。输出 $cnt$ 与此时的 $sum_i$ 即可。

## [AC代码](https://www.luogu.com.cn/record/153148762)

```
#include<bits/stdc++.h>
using namespace std;
int n,a,sum[80],ans,cnt;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++)cin>>a,sum[a]++;
    for(int i=75;i>=0;i--){
        if(sum[i]!=0)cnt++;
        if(cnt==3){ans=sum[i];cnt=i;break;}
    }
    cout<<cnt<<" "<<ans;
}
```

~~话说为啥对了只有那么点分~~

---

## 作者：I_Love_DS (赞：3)

## 闲话

因为本题超级超级简单，~~所以我们应该精益求精~~。

## 思路

我发现有很多大佬用的 `sort()` 和 `unique()`，~~非常复杂，本人蒟蒻就是不会，怎么办呢？~~

其实快排在本题并不适用，最高效的当属**计数排序**。

记录每个分值的人数，再把记录分值人数的数组从大到小扫一遍，找到的第三个不为 $0$ 的分值人数，输出分值和得到的该分值的人数即可。

### 时间复杂度

读入时间 $O(n)$，计数排序 $O(n)$，所以总时间复杂度 $O(n)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,a,cnt[80],s = 75 + 1,ans = 0;
int main(){
	scanf("%d",&n);
	for (int i = 1; i <= n; i++) scanf("%d",&a),cnt[a]++;
	do {s--; ans += cnt[s] != 0;} while (ans != 3);
	printf("%d %d",s,cnt[s]);
	return 0;
}
```

谢谢观看。如果有疑问请在评论区留言，我会尽量看的！

---

## 作者：wyf1230 (赞：2)

本蒟蒻水平有限，只会用 sort 排序后一个个寻找，然后计数输出,具体请见注释。
```
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,fs=0,ans=1;
	cin>>n;
	int a[n+1];
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);//sort排序
	int cs=1; //用来分辨是第几高的分数
	for(int i=n;i>=1;i--){
		if(cs>3)break;//没有奖牌
		if(cs==3){//铜牌
			fs=a[i];//分数
			if(a[i]==a[i-1]) ans++;//同分人数
		}
		if(a[i]!=a[i-1]) cs++;
	}
	 cout<<fs<<" "<<ans;//输出
         return 0;
}
```

---

## 作者：xinxin2022 (赞：1)

# 题目大意

求一个数组中第三大的数是什么，出现了几次。

# 题目思路

这道题的普通思路是暴力枚举，不过我今天给大家带来一种更为~~优秀且快速~~简洁的思路：**快速排序**。

我们可以对数组从小到大排序，然后逆序查找第三大的数，找到后输出对应的分数，再统计该分数出现的次数，最后输出。

# AC Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,l=1,ans=0;//l为1时表示金牌，为2时表示银牌，为3时表示铜牌
    cin>>n;
    int a[n+1];
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    sort(a+1,a+1+n);
    //sort(起始下标,结束下标+1);
    for(int i=n-1;i>=1;i--)//从大到小遍历数组
    {
        if(a[i]<a[i+1]) l++;//如果分数发生变化，则表明已经遍历完了获得同一个分数的所有人
        if(l==3) //当l为3时说明已经遍历到了获得铜牌的人
        {
            if(!ans) cout<<a[i]<<" ";
          //为了避免重复输出
            ans++;
          //统计获得铜牌的人数
        }
    }
    cout<<ans;//输出获得铜牌的人数
    return 0;
}
```

---

## 作者：Mason123456 (赞：1)

## [P10292](https://www.luogu.com.cn/problem/P10292)

### 朴素做法 —— 堆

每次记录堆顶元素，三个 `while` 循环判断输出，时间复杂度 $O(n\times \log n)$，不知道是不是卡常，最后得分 0pts。

```cpp
#include <bits/stdc++.h>
using namespace std;
priority_queue<int> q;
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i = 1;i <= n;i++){
		int c;
		cin>>c;
		q.push(c);
	}
	int f = q.top();
	while(q.top() == f)	q.pop();
	f = q.top();
	while(q.top() == f)	q.pop();
	f = q.top();
	int cnt = 0;
	while(q.top() == f)	q.pop(), cnt++;
	cout<<f<<" "<<cnt;
}
```

### 开桶去重，再排序

为什么想到开桶呢，看数据范围，$0 \le s \le 75$，这么小，不就是让我们开桶用的吗？但不过需要注意，开桶虽然有去重的意思，但是还要用桶统计分数的出现次数。时间复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 80;
int t[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cin>>n;
	for(int i = 1;i <= n;i++){
		int c;
		cin>>c;
		t[c]++;
	}
	int cnt = 0;
	for(int i = N;i >= 0;i--){
		if(t[i])	cnt++;
		if(cnt == 3){
			cout<<i<<" "<<t[i];
			return 0;
		}
	}
}
```

### 遍历一遍数组，维护第三大值

主要思路就是开三个变量，分别是最大值，次大值，第三大值。再输入的时候维护三个变量即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 80;
int t[N];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	int a = -1, b = -2, c = -3;
	int an = 0, bn = 0, cn = 0;
	cin>>n;
	for(int i = 1;i <= n;i++){
		int r;
		cin>>r;
		if(r == a)	an++;
		else if(r == b)	bn++;
		else if(r == c)	cn++;
		else if(r > a){
			c = b, cn = bn;
			b = a, bn = an;
			a = r, an = 1;
		}
		else if(r > b){
			c = b, cn = bn;
			b = r, bn = 1;
			
		}
		else if(r > c){
			c = r, cn = 1;
		}
		
	}
	cout<<c<<" "<<cn;
}
```

---

## 作者：封禁用户 (赞：1)

## [题目传送门](https://www.luogu.com.cn/problem/P10292)

## 思路

水。

我们用 $b_x$ 记录 $x$ 在所有参赛选手的分数中出现的次数；$p$ 记录当前出现的所有分数中的最小值，初始值为 $a_1$；$cnt$ 表示当前分数是第 $cnt$ 大的分数。

输入 $n$ 和 $a$ 数组，表示所有参赛选手的分数，从大到小排序，如果 $a_i=p$，说明当前出现的所有分数中的最小值没有更新，跳过；否则，更新最小值，把 $cnt$ 加 $1$，如果 $cnt=3$，说明找到了第 $3$ 大的分数，符合铜牌的要求，所以要输出当前分数和它的出现次数，即 $a_i$ 和 $b_{a_i}$，然后结束程序。

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
int a[2000010], b[2000010];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
    	cin >> a[i];
    	b[a[i]]++;
    }
    sort(a + 1, a + 1 + n, greater<int>());
    int p = a[1], cnt = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] == p) continue;
        if (a[i] < p) {
            p = a[i];
            cnt++;
            if (cnt == 3) {
                cout << a[i] << " " << b[a[i]] << endl;
                return 0;
            }
        }
    }
    return 0;
}
```

---

## 作者：2021zjhs005 (赞：1)

考虑到 $1\leq s\leq 75$，我们可以用一个桶来统计分数为 $i$ 的人数 $a_i$。

然后倒着循环，从上限 $75$ 到下限 $0$（注意不是 $1$），如果 $a_i > 0$ 则 $ans \gets ans+1$，当 $ans=3$ 直接输出，并结束程序。

并不用考虑 $n\leq 2$ 的情况，这样问题 $1$ 就回答不上来了，所以无需考虑。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define rep(i,x,y) for(register int i=x;i<=y;i++)
#define rrep(i,x,y) for(register int i=x;i>=y;i--)
#define pr printf
inline int read(){int s=0,w=1;char c=getchar();while(!isdigit(c)){if(c=='-') w=-1;c=getchar();}while(isdigit(c)){s=(s<<1)+(s<<3)+(c^48);c=getchar();}return s*w;}

int n,cnt,a[80];

signed main(){
  n=read();
  rep(i,1,n){
    int x=read();
    a[x]++;//该人分数为 x，对 a[x] 的贡献为 1。
  }
  rrep(i,75,0){
    if(a[i]) ++cnt;
    if(cnt==3){//桶牌。
      pr("%lld %lld\n",i,a[i]);
      exit(0);
    }
  }
}
```

---

## 作者：fried_chicken (赞：0)

# 题意：
给你一串数，你要降序排列，求出第三大的数并求出第三大的数在这串数里出现几次

# 分析：

我们可以使用三个循环，第一个循环用来输入，第二个用来统计第三大的数是什么，第三个用来累加

寻找第三大的数时，我们要保证前一个数不等于后一个数。如果最大的数有两个，第二大的数有一个，你不判断你前一个数不等于后一个数你求出来的第三大就是第二大


代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[1000001],n,rk,cnt=0,th;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){//输入
		cin>>a[i];
	}sort(a+1,a+n+1,greater<int>());//降序排列
	for(int i=1;i<=n;i++){//寻找第三大
		if(a[i]!=a[i+1]){
			rk++;//统计这是第几大
		}
		if(rk==3){//如果是第三大就存下来第三大是什么
			th=a[i];
			break;
		}
	}for(int i=1;i<=n;i++){//统计
		if(a[i]==th) cnt++;
	}
	cout<<th<<' '<<cnt;//输出
	return 0;
}
```

---

## 作者：a_little_carrot (赞：0)

~~蒟蒻第一第二篇题解被打回后的第三篇题解~~。

~~这题好难~~ 这题挺简单的，数据范围看着很唬人，但其实还好。

主要思路就是用桶标，因为 $0 \le n \le 75$，数据范围不大。然后就找有人并且倒数第三大的分数。

废话少说，上代码。

```cpp
#include <bits/stdc++.h>
using namespace std ;
int n,s ;
int f[80],p ;
int main() {
    cin>>n ;//                  ↓桶
    for(int i=1;i<=n;i++)cin>>s,f[s]+=1 ;//统计次数
    for(int i=75;i>=0;i--) {
    	if(f[i])p++ ;
    	if(p==3) {
    		cout<<i<<' '<<f[i] ;
    		break ;
		}
    }
    return 0 ;
} 
```

---

## 作者：LG086 (赞：0)

### 分析

输入 $N$ 个数，输出其中第三大的数 $k$ 以及一共多少个数等于 $k$。  
因为每个数 $a$ 都满足 $0 \le a \le 75$，所以使用数组计数。从后往前，找第三大的数，找到就输出。

------------
### 代码

```cpp
#include<iostream>
#define int long long
#define LG086 signed
LG086 main(){
    int n,i,x,top=3,a[80]={0};std::cin>>n;
    for(i=0;i<n;i++)std::cin>>x,a[x]++;
    for(i=75;i>=0;i--)
        if(a[i]>0)
            if(top>1){top--;}
            else if(top==1)
                return std::cout<<i<<" "<<a[i],0;
}
```

---

## 作者：LostKeyToReach (赞：0)

一道水题。

我们将所有分数排序，然后去重，取第三大的分数，再遍历**原来**每个选手的分数比较一下就行了，时间复杂度 $O(n \log n)$。

代码十分简短，就不放了。

---

## 作者：_Jocularly_ (赞：0)

输入数字后，统计每一个数字出现的个数，因为最大的分数就是七十五，那么我们从七十五开始从大到小枚举，如果这个数出现过，计数器加一，如果加到了第三个，那么说明这个分数就是铜牌的分数，保存下来，输出这个数和它出现的次数即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int now;
int a[250005],cnt[250005];
int bronze,num;
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		cnt[a[i]] ++;
	}
	for(int point=75;point>=0;point--){
		if(cnt[point]) now ++;
		if(now == 3){
			bronze = point;
			break;
		}
	}
	num = cnt[bronze];
	cout << bronze << " " << num;
	return 0;
}

```

---

## 作者：we_are_the_chuibing (赞：0)

将所有分数排序，然后一个一个遍历，找到第三的分数，并数有多少人都是这个分数。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[300005]={-1},k,ans;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	sort(a+1,a+n+1);
	for(int i=n-1;i>=1;i--){
		if(a[i]!=a[i+1])k++;
		if(k==2){
			cout<<a[i]<<" ";
			int q=i;
			while(true){
				ans++;
				q--;
				if(a[q]!=a[q+1]){
					cout<<ans;
					return 0;
				}
			}
		}
	}
	return 0;
}
```

可能有人不懂，为什么我要把数组的第一个位置设成 $-1$，是因为存在第一个人分数为 $0$ 的情况，如果这个分数恰好是第三的话会导致多计算。

---

