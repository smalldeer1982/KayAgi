# Valera and Contest

## 题目描述

Valera loves to participate in competitions. Especially in programming contests. Today he has participated in the contest with his team, consisting of $ n $ students (including Valera). This contest was an individual competition, so each student in the team solved problems individually.

After the contest was over, Valera was interested in results. He found out that:

- each student in the team scored at least $ l $ points and at most $ r $ points;
- in total, all members of the team scored exactly $ s_{all} $ points;
- the total score of the $ k $ members of the team who scored the most points is equal to exactly $ s_{k} $ ; more formally, if $ a_{1},a_{2},...,a_{n} $ is the sequence of points earned by the team of students in the non-increasing order $ (a_{1}>=a_{2}>=...>=a_{n}) $ , then $ s_{k}=a_{1}+a_{2}+...+a_{k} $ .

However, Valera did not find out exactly how many points each of $ n $ students scored. Valera asked you to recover any distribution of scores between the students of the team, such that all the conditions above are met.

## 样例 #1

### 输入

```
5 3 1 3 13 9
```

### 输出

```
2 3 2 3 3 ```

## 样例 #2

### 输入

```
5 3 1 3 15 9
```

### 输出

```
3 3 3 3 3 ```

# 题解

## 作者：Mingci (赞：2)

# CF369B Valera and Contest
[题目传送门](https://www.luogu.com.cn/problem/CF369B)
## 题目大意:
有 $N$ 个选手，每个选手至少 $l$ 分，至多 $r$ 分，所有选手成绩总和是 $s_{all}$，前 $k$ 个选手成绩总和是 $s_k$，现在要求所有选手成绩分别是多少。
## 题目分析：
本题主要是模拟，一个平摊的思想，也就是将总分平均分给每一个选手来求出每一个选手各自的成绩，其余的大部分思路会在代码注释中讲解。
## 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int n,k,sa,sk,l,r,s;//意义见题目大意
int a[maxn];//用a数组维护每个选手的分数
int main(){
	cin >> n >> k >> l >> r >> sa >> sk;//输入顺序没在翻译里给出就很坑
	for(register int i = 1;i <= n;++i)a[i]+=l;//将每个选手的得分调整到最小值
	s=sk-k*l;//前k名的选手瓜分属于他们的分数
	for(register int i = 1;s>0;++i){//一直循环到分完为止
		if(i>k)i=1;//判断i是否大于k，大于说明超过了前k个的范畴，要揪回来
		a[i]++;//第i个选手分到一分
		s--;//可分总分减少一分
	}
	s=sa-(n-k)*l-sk;//接下来后n-k名同学瓜分剩余的分数
	for(register int i = k+1;s>0;++i){
		if(i>n)i=k+1;//同上，也可用取模运算实现
		a[i]++;//分得一分
		s--;//可分总分减一分
	}
	for(register int i = 1;i <= n;++i)cout << a[i] << " ";//按序输出
	return 0;//华丽结束
}

```


---

## 作者：sz_jinzikai (赞：2)

[洛谷传送门](https://www.luogu.com.cn/problem/CF369B)&[CF 传送门](https://codeforces.com/problemset/problem/369/B)
# 思路
首先，我们把这 $n$ 个人拆分成前 $k$ 个人和后面的 $n-k$ 个人。处理前 $k$ 个人，我们可以采取均摊的方法：把 $s_k$ 差分成 $s_k\bmod k$ 个 $\lfloor\frac{s_k}{k}\rfloor$ 和剩下的 $k-s_k\bmod k$ 个 $\lceil\frac{s_k}{k}\rceil$，这样就很好做了！另外，剩下的 $n-k$ 个人也同理，这里就不详细展开了。
# 代码
```cpp
# include <bits/stdc++.h> //万能头
using namespace std;
int n, k, l, r, sall, sk; //定义变量
int main () { //定义主函数
	cin >> n >> k >> l >> r >> sall >> sk; //读入
	for (int i = 0; i < sk % k; ++ i) //枚举前 k 个人的向上取整部分
		cout << sk / k + 1 << ' '; //输出向上取整的分数
	for (int i = 0; i < k - sk % k; ++ i) //枚举前 k 个人的向下取整部分
		cout << sk / k << ' '; //输出向下取整的分数
	n -= k; //计算后 n-k 个人的人数
	sall -= sk; //计算后 n-k 个人的总分
	if (! n) //这里有个毒瘤数据要注意，就是 n=k，如果不加特判后面就会除以 0，导致 RE
		return 0; //直接返回了
	for (int i = 0; i < sall % n; ++ i) //枚举后 n-k 个人的向上取整部分
		cout << sall / n + 1 << ' '; //输出向上取整的分数
	for (int i = 0; i < n - sall % n; ++ i) //枚举后 n-k 个人的向下取整部分
		cout << sall / n << ' '; //输出向下取整的分数
	return 0; //结束程序
}
```

---

## 作者：shaocy (赞：2)

本蒟蒻又来提交题解了，麻烦给我点个赞吧！

我们就按着题目要求一步一步慢慢做就好了（手动滑稽~

先对k个处理，先处理sk%k个为sk/k+1,如果sk/k==0，k个数都为sk/k；对与剩下的数也按照同样的方法处理，处理完之后就是所要求的序列。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1100;
int  sorce[maxn],n,k,l,r,sall,sk;
int main()
{
    cin>>n>>k>>l>>r>>sall>>sk;
    for(int i=1;i<=k;i++)
    {
        sorce[i]=sk/k;
    }
    int t=sk%k,i=1;
    while(t)
    {
        t--; sorce[i++]++;
    }
    if(k!=n)
    {
        for(int i=k+1;i<=n;i++)
        {
            sorce[i]=(sall-sk)/(n-k);
        }
        int t,i;
        t=(sall-sk)%(n-k),i=k+1;
        while(t)
        {
            t--; sorce[i++]++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        cout<<sorce[i]<<" ";
    }
    return 0;
}
```


---

## 作者：_shine_ (赞：1)

有 $n$ 个数 $a_i$，所有的数满足 $l\le a_i \le r$，并且 $\sum_{i=0}^{n}a_i=s_{all}$ 以及 $\sum_{i=0}^{k}a_i=s_K$ 的序列。

既然是要让总和以及上下线有要求，则不妨把前 $k$ 个与后 $n-k$ 个分类讨论，先满足前 $k$ 大的再进行微微调整。显然，所有的都要尽量的进行平均分（这样好做，其他也可以），及前 $k$ 大的平均分 $\left \lfloor \frac{s_K}{k} \right \rfloor $，以及再分发下 $s_K \bmod k$ 留下的几个，再把剩下的$\frac{n-k}{s_{all}-s_K}$ 平均分下，进行微微调整即可。

但，请注意 $n=k$ 时的情况，需要跳过。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n,k,l,r,all,onces;
int a[maxn];
signed main(){
	cin >> n >> k >> l >> r >> all >> onces;	
	for(int i=1;i<=k;i++){
        a[i]=onces/k;
    }
    int t=onces%k,idx=1;
    while(t){
        a[idx++]++;
        t--;
    }
    if(k!=n){
        for(int i=k+1;i<=n;i++){
            a[i]=(all-onces)/(n-k);
        }
        t=(all-onces)%(n-k),idx=k+1;
        while(t){
            t--;
			a[idx++]++;
        }
    }
    for(int i=1;i<=n;i++){
        cout << a[i] << " ";
    }
	return 0;
}
```


---

## 作者：_rxfalty_ (赞：1)

## [题目描述](https://www.luogu.com.cn/problem/CF369B)
在题目中，总共有 $n$ 个人参加比赛，每个人的分数在 $l$ 和 $r$ 之间，所有选手的分数和为 $s_{all}$，分数前 $k$ 大的选手的分数和为 $s_k$。

## 思路
一道简单的模拟题，可以先求出前 $k$ 大的每个选手的分数，再求出其他选手的分数。

## 代码
```c++
#include<bits/stdc++.h>
using namespace std;
int n,l,r,sall,k,sk,a[100005];
int main(){
	cin>>n>>k>>l>>r>>sall>>sk;
	for(int i=1;i<=n;i++){
		a[i]=a[i]+l;
	}
	int t1=sk-k*l;
	for(int i=1;t1>0;i++){//求前k个选手的分数 
		if(i>k){
			i=1;
		}
		a[i]++;
		t1--;
	}
	int t2=sall-(n-k)*l-sk;
	for(int i=k+1;t2>0;i++){//求剩余选手的分数 
		if(i>n){
			i=k+1;
		}
		a[i]++;
		t2--;
	}
	for(int i=1;i<=n;i++){
		cout<<a[i]<<" ";
	}
	return 0;
}
```

---

## 作者：xueruo (赞：1)

# [题意](https://www.luogu.com.cn/problem/CF369B)   
构造出任意一个序列 $a$。有 $n$ 个元素，$a_i \in [l,r]$，$\displaystyle\sum_{i=1}^n a_i=s_{all}$，并且前 $k$ 大的数和为 $s_k$ 请输出序列（顺序无所谓）。  
# 思路
先对前 $k$ 个摊平处理，计算出这段区间的每个分数 $score_i=\frac{all-s_k}{n-k}$。  
剩下的 $[k+1,n]$ 的数也按照同样的方法计算，最后输出序列。   
```cpp
#include<iostream>
#define int long long
#define f(i,j,n) for(register int i=j;i<=n;++i)
inline int read(){
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-') 
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * f;
}
inline void write(int x){
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
using namespace std;
const int N=1e4+10;
int score[N];
signed main(){
	register int n=read(),k=read(),l=read(),r=read(),all=read(),s_k=read();
	
	f(i,1,k)score[i]=s_k/k;//先将s_k平摊着放下去 
	//再从前往后依次放剩余的
	register int tmp=s_k-(s_k/k*k),i=1;
	//tmp 表示多出来的 
	while(tmp--){
		++score[i];
		++i;
	}
	//后面的差不多一样处理 
	if(k!=n){//不是最后一个 
		f(i,k+1,n)score[i]=(all-s_k)/(n-k);//将(all-s_k)平摊着放下去 
		//再从前往后依次放剩余的
		register int tmp=(all-s_k)-(all-s_k)/(n-k)*(n-k),i=k+1;
		while(tmp--){
			++score[i];
			++i;
		}
	}
	f(i,1,n)cout<<score[i]<<" ";
	return 0;
}
/*
in
5 3 1 3 13 9
out
2 3 2 3 3 
*/
```

---

## 作者：yigexiaobai (赞：0)

# CF369B Valera and Contest
[题目传送门](www.luogu.com.cn/problem/CF369B)
## 题意
一场比赛有 $n$ 个选手参加，每个选手的分数至少为 $l$ 分，至多为 $r$ 分，所有选手分数总和为 $s_{all}$，且前 $k$ 名的选手的分数和为 $s_{k}$，现在要得到满足条件的所有选手的分数。
## 分析
用平摊的思想，我们可以先求出前 $k$ 名选手的分数，在求出剩余选手的分数。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,k,l,r,s1,s2,s;
int a[100005];
int main(){
	scanf("%d%d%d%d%d%d",&n,&k,&l,&r,&s1,&s2);
	for(int i=1;i<=n;i++) a[i]+=l;//每名选手分数调为最小值
	s=s2-k*l;//前k名选手的分数
	for(int i=1;s>0;i++){
		if(i>k){
			i=1;
		}//判断i是否超过k,超过就归位
		a[i]++;//第i名选手分数加一
		s--;//总分减一
	}
	s=s1-(n-k)*l-s2;//剩余选手的分数
	for(int i=k+1;s>0;i++){
		if(i>n){
			i=k+1;
		}
		a[i]++;
		s--;
	}//同上
	for(int i=1;i<=n;i++) printf("%d ",a[i]);//输出
	return 0;//完结撒花
}
```


---

## 作者：zhouweixi0 (赞：0)

# CF369B
## 前情提要
感谢来自 @shaocy 的思路！

这篇题解我会写得尽量详细一些。
## 题意
[题目传送门](https://www.luogu.com.cn/problem/CF369B)

有一场比赛，有 $n$ 个选手参加，每个选手至多 $r$ 分，至少 $l$ 分，分数总和为 $s_{all}$ 分，分数前 $k$ 大的选手总分为 $s_k$ 分，求所有选手的分数。

我们可以先处理前 $k$ 个选手的分数，再去处理剩下的分数。

具体实现过程我会在代码中提到。话不多说，上代码！
## 代码
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l,r,sall,sk,x=1;
int s[1000001];//这个数组用来存储每个选手的成绩
int main(){
    cin>>n>>k>>l>>r>>sall>>sk;
    for(int i=1;i<=k;i++){
        s[i]=sk/k;//将前k个选手的分数平均分配
    }
    int ohno=sk%k;//由于平均分有可能是小数，而整除会忽略小数，所以会有剩余，这里的ohno就是剩余的量
    while(ohno--){
        s[x]++;//将剩余的量尽量平均分配
        x++;
    }//因为我们已经做到了最平均，所以不用考虑l和r
    if(n-k){//如果还有剩余
        for(int i=k+1;i<=n;i++){
            s[i]=(sall-sk)/(n-k);//重复之前操作，将剩下的分值分给剩下的选手
        }
        ohno=(sall-sk)%(n-k);//将这次分配剩余的量记录
        x=k+1;//下标
        while(ohno--){
            s[x]++;//平均分配
            x++;
        }
    }
    for(int i=1;i<=n;i++){
        cout<<s[i]<<" ";//最后，输出所有选手的分数
    }
    return 0;//完结撒花~
}
~~~


---

## 作者：zsh_haha (赞：0)

### 思路讲解

我们先看 $l,r$，有些同学看到分数要求就有些发难了，但是，由于 CF 给的数据总不会无解吧？所以只要方法正确我们就可以~~放弃~~不用 $l,r$。

我们先考虑前 $k$ 名选手，前 $k$ 名选手的平均分显然是 $\frac{s_k}{k}$，但是这里不能有小数，所以我们先给前 $k$ 名选手每人 $\lfloor\frac{s_k}{k}\rfloor$ 分，再给前 $s_k\bmod k$ 每人 $1$ 分，正好分完。

然后后 $n-k$ 名选手也是如此，注意这里有个坑：要考虑 $n-k=0$ 的情况，如果 $n-k=0$ 需要直接跳过，否则循环的时候除以零或模零都是会 RE 的。

### AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,l,r,s_all,s_k;
	cin>>n>>k>>l>>r>>s_all>>s_k;
	for(int i=1;i<=s_k%k;i++){
		cout<<s_k/k+1<<' ';
	}
	for(int i=s_k%k+1;i<=k;i++){
		cout<<s_k/k<<' ';
	}
	s_all-=s_k;
	n-=k;
	if(n==0){
		return 0;
	}
	for(int i=1;i<=s_all%n;i++){
		cout<<s_all/n+1<<' ';
	}
	for(int i=s_all%n+1;i<=n;i++){
		cout<<s_all/n<<' ';
	}
    return 0;
}
```

---

