# Drinks Choosing

## 题目描述

Old timers of Summer Informatics School can remember previous camps in which each student was given a drink of his choice on the vechorka (late-evening meal). Or may be the story was more complicated?

There are $ n $ students living in a building, and for each of them the favorite drink $ a_i $ is known. So you know $ n $ integers $ a_1, a_2, \dots, a_n $ , where $ a_i $ ( $ 1 \le a_i \le k $ ) is the type of the favorite drink of the $ i $ -th student. The drink types are numbered from $ 1 $ to $ k $ .

There are infinite number of drink sets. Each set consists of exactly two portions of the same drink. In other words, there are $ k $ types of drink sets, the $ j $ -th type contains two portions of the drink $ j $ . The available number of sets of each of the $ k $ types is infinite.

You know that students will receive the minimum possible number of sets to give all students exactly one drink. Obviously, the number of sets will be exactly $ \lceil \frac{n}{2} \rceil $ , where $ \lceil x \rceil $ is $ x $ rounded up.

After students receive the sets, they will distribute their portions by their choice: each student will get exactly one portion. Note, that if $ n $ is odd then one portion will remain unused and the students' teacher will drink it.

What is the maximum number of students that can get their favorite drink if $ \lceil \frac{n}{2} \rceil $ sets will be chosen optimally and students will distribute portions between themselves optimally?

## 说明/提示

In the first example, students could choose three sets with drinks $ 1 $ , $ 1 $ and $ 2 $ (so they will have two sets with two drinks of the type $ 1 $ each and one set with two drinks of the type $ 2 $ , so portions will be $ 1, 1, 1, 1, 2, 2 $ ). This way all students except the second one will get their favorite drinks.

Another possible answer is sets with drinks $ 1 $ , $ 2 $ and $ 3 $ . In this case the portions will be $ 1, 1, 2, 2, 3, 3 $ . Then all the students except one will gain their favorite drinks. The only student that will not gain the favorite drink will be a student with $ a_i = 1 $ (i.e. the first, the third or the fourth).

## 样例 #1

### 输入

```
5 3
1
3
1
1
2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10 3
2
1
3
2
3
3
1
3
1
2
```

### 输出

```
9
```

# 题解

## 作者：meyi (赞：5)

我们可以倒过来考虑：在已有的n个元素中找出能组成二元组的元素。显而易见，设一个元素出现 $k$ 次，那么它就能组成 $\lfloor\frac{k}{2}\rfloor$ 个二元组。所以，对于一个出现 $k$ 次的元素，我们的累加器 $s$ 只需加上 $\lfloor\frac{k}{2}\rfloor$ 即可，最后输出 $s*2$ 即可

但要注意可能会有 $s<\lceil\frac{n}{2}\rceil$ 的情况，这时，应该输出 $s*2+\lceil\frac{n}{2}\rceil-s$ ，即 $s+\lceil\frac{n}{2}\rceil$ (其实，当 $s=\lceil\frac{n}{2}\rceil$ 时，输出的就是上文的 $s*2$ )

等价程序：
```cpp
#include<cstdio>
int a[1001],k,n,s;	//a:记录出现次数的数组；k,n:同题意；s:累加器
main(){
    scanf("%d%d",&n,&k),k=(n&1)+(n>>1);	//k在本题中并没有作用，因此将它赋值为ceil(n*0.5)
    while(n--)scanf("%d",a),s+=a[*a]++&1;	//累加当前元素能够组成的二元组的个数
    printf("%d",k+s);	//输出，分析见上文
} 
```


---

## 作者：闫登科 (赞：1)

~~其实这是个水题。~~（没错就是个水题）    
其实用贪心的方法就行了。   
我们看到k<1000其实就应该懂了；   
先用桶把所有的数做一个统计，然后跑一遍for循环得到a[i]%2的结果，               
再将a[i]%2的结果相加除以二就行了，  最后将（(a[i]/2)*2）（别忘了乘2）和a[i]%2的结果之和向上取整就行；

附上代码；
```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int n,m;
int a[1050],ans=0,ans2=0;//ans是(a[i]/2)*2的结果，ans2是a[i]%2之和。
 
void readin()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        int b;
        scanf("%d",&b);
        a[b]++;
    }
}
void work()
{
    readin();
    for(int i=1;i<=m;i++)
    {
        ans=ans+(a[i]/2)*2;//别忘除2
        a[i]=a[i]%2;
        ans2+=a[i];
    }
    ans=(ans2+1)/2+ans;
    printf("%d",ans);
}
int main()
{
    work();
    return 0;
 } 
 
```




---

## 作者：Konnyaku_ljc (赞：1)

看完题解后我想：就我的想法那么奇特吗？后来发现——本质都是一样的。  
我先将总的饮料存下，计算饮料组数，排序后去掉两两相同的，在sum中减去，单个的再减一遍sum，剩下的sum便是无法满足的数的相反数，n-|sum|既n+sum便是满足的人数
```cpp
#include<cstdio>
#include<cmath>
#include<algorithm>//头文件
using namespace std;
int n,k,a[1005],sum;
//n、k为题目要求，a数组为输入喜欢的饮料，sum计算饮料组数
int main()
{
	scanf("%d%d",&n,&k);//输入
	if(n%2==0) sum=n/2;
	else sum=n/2+1;  //计算sum（组数）
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);//输入喜欢的饮料
	sort(a+1,a+1+n);//排序，保证前后一样
	for(int i=2;i<=n;i++)
	{
		if(a[i]==a[i-1]) a[i]=0,a[i-1]=0,sum--;
        //相等时，便都清零，组数——
	}
	for(int i=1;i<=n;i++)
	{
		if(a[i]!=0) sum--;
       //sum为还剩的组数，一旦有可以满足的，就少一种
       //最后，便是不能满足的组数的相反数（懒得证明，一眼题）
	}
	printf("%d",n+sum);//输出
	return 0;
}
```


---

## 作者：_bql (赞：1)

算是数学解法？
先统计一下喜欢每种饮料的有多少人（s数组）
然后直接能满足就满足
直接看重要部分代码 会有比较清楚的注释
```cpp
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>a[i];
		s[a[i]]++;//统计喜欢每种饮料的有多少人
	}
	n+=n%2;//小处理 以保证/2之后向上取整
	n/=2;
	for(int i=1;i<=k;i++)
	{
		ans+=s[i]/2*2;//能满足就满足
		n-=s[i]/2;//n减去相应的值
	}
	ans+=n;
	cout<<ans;
```


---

## 作者：tommychen (赞：0)

> 一道大水题。

### 题面
[洛谷题面](https://www.luogu.com.cn/problem/CF1195A)

[CF题面](https://codeforces.com/contest/1195/problem/A)

### 题意
题意请自己阅读洛谷翻译（很好懂的）。

### 思路
简单贪心题。

为了使相同的数最多，我们要尽量让二元组中每一个元素都用上。我们统计这些成对的数的个数，让其他的二元组全部用来了满足单独的数就可以了（贪心策略明显正确）。

最后输出成对的数的个数 $*2$ 加剩下二元组的个数即可。

### 代码
```cpp
#include<bits/stdc++.h>
#include<algorithm>
#define int long long
using namespace std;
signed main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	//MessageBox(GetForegroundWindow(),"标题","内容",MB_YESNO);
	int n,m;
	cin>>n>>m;
	int a[n+1],tot[m+1]={0};
	for(int i=1;i<=n;i++){
		cin>>a[i];
		tot[a[i]]++;//统计每个数出现的个数，方便后面计算成对的数
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		sum+=tot[i]/2;//统计有多少个成对的数
	}
	int ans=n-n/2;//上取整
	ans-=sum;//剩下可以使用的二元组个数
	cout<<sum*2+ans<<endl;//输出答案
	return 0;
}

```


---

## 作者：oimaster (赞：0)

> 多么水的一道题啊，简直是优先队列模板！

> 什么？没有人用优先队列？优先队列会伤心的！

这篇题解将会使用优先队列来解决这道水题。![cy](https://cdn.luogu.com.cn/upload/pic/62225.png)![xyx](https://cdn.luogu.com.cn/upload/pic/62230.png)

我们把喜欢每种饮料的人数统计出来，然后扔到一个优先队列（大根堆）里去。

我们手动模拟 $\lceil\frac{n}{2}\rceil$ 次。
- 如果这时堆里没有任何东西，我们就跳出循环。
```cpp
if(pq.empty())
    break;
```
- 如果堆顶的值大于 $2$，也就是这种饮料需要若干集合才能全部满足，我们就暂时满足 $2$ 个同学，剩下的仍然扔到堆中。
```cpp
cnt+=2;
int tmp=pq.top();
pq.pop();
pq.push(tmp-2);
```
- 否则，我们就弹出堆顶，并且满足那 $1$ 位或 $2$ 位同学。
```cpp
cnt+=pq.top();
pq.pop();
```

然后我们来看看这样做能不能保证尽可能满足最多的同学数量。因为这是一个大根堆，可以发现这种方法可以保证以下几点：

- 能一次满足 $2$ 位同学就不会满足别的同学。
- 如果我们正在满足 $1$ 位同学，那么堆中剩余下来的元素也一定全是 $1$。

分析以下复杂度，枚举循环是 $\lceil\frac{n}{2}\rceil$ 轮，里面每次对堆进行操作是 $\log$ 级别，所以总复杂度是 $\text{O}(n\log n)$。其实这题随便玩玩就能过。

```cpp
#include<iostream>
#include<queue>
using namespace std;
priority_queue<int>pq;
int main(){
	int n,k;
	cin>>n>>k;
	int a[n+1];
	for(int i=1;i<=n;++i)
		cin>>a[i];
	int d[k+1];
	for(int i=1;i<=k;++i)
		d[i]=0;
	for(int i=1;i<=n;++i)
		++d[a[i]];
	for(int i=1;i<=k;++i)
		if(d[i]!=0)
			pq.push(d[i]);
	int m=(n+1)/2;
	int cnt=0;
	while(m--){
		if(pq.empty())
			break;
		if(pq.top()<=2){
			cnt+=pq.top();
			pq.pop();
		}
		else{
			cnt+=2;
			int tmp=pq.top();
			pq.pop();
			pq.push(tmp-2);
		}
	}
	cout<<cnt<<endl;
}
```

---

## 作者：寒鸽儿 (赞：0)

[luogu博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-CF1195A)   
[本题解同步发表于作者的个人博客](https://froldh.github.io/2019/07/22/codeforcesPlan/CF1195/)  
这题很显然是一个贪心，能够配对的配对，不能的则有一半(上取整)能配对。    
考虑k<=1000 ,所以只要开桶来存储即可。   
假设这题k再大些，就要离散化，再大就要hash。  
```cpp
#include <cstdio>

using namespace std;

const int maxk = 1010;
int a[maxk];

int main() {
	int n, k, lft = 0, t;
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &t);
		if(a[t]) lft--;
		else lft++;
		a[t] ^= 1;
	}
	printf("%d\n", n - lft + (lft + 1) / 2);
	return 0;	
}
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  

---

## 作者：小黑AWM (赞：0)

> *大水题，都怪题意晦涩我竟在16min的时候才切掉！*


题意就不阐释了。为了使相同的个数最大，所以我们要尽量使一个二元组中的两个数都有用，把成对的相同元素消掉后，再把单个元素用一个二元组消掉，这样子贪心的做法，是明显正确的。

```cpp
/*
 * Author: xiaohei_AWM
 * Date: 7.17
 * Mutto: Face to the weakness, expect for the strength.
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<utility>
#include<functional>
#include<cmath>
#include<vector>
#include<assert.h>
using namespace std;
#define reg register
#define endfile fclose(stdin);fclose(stdout);
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef std::pair<int,int> pii;
typedef std::pair<ll,ll> pll;
namespace IO{
    char buf[1<<15],*S,*T;
    inline char gc(){
        if (S==T){
            T=(S=buf)+fread(buf,1,1<<15,stdin);
            if (S==T)return EOF;
        }
        return *S++;
    }
    inline int read(){
        reg int x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
    inline ll readll(){
        reg ll x;reg bool f;reg char c;
        for(f=0;(c=gc())<'0'||c>'9';f=c=='-');
        for(x=c^'0';(c=gc())>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^'0'));
        return f?-x:x;
    }
}
using namespace IO;
int n, k, a[1010], t, cnt[1010], ans;
int main(){
    n = read(), k = read();
    for(int i = 1; i <= n; i++)
        a[i] = read(), cnt[a[i]]++;//我们记录一下相同的元素个数，这样子再消掉的时候方便处理
    if(n & 1) t = (n+1)/2;
    else t = n/2;
    for(int i = 1; i <= k && t > 0; i++){
        int temp = cnt[i]/2;
        if(temp <= t){
            t -= temp;
            ans += 2*temp;
            cnt[i] -= 2*temp;
        }else{
            t = 0;
            ans += 2*t;
            cnt[i] -= 2*t;
        }
    }
    if(t > 0) ans += t;
    cout << ans << endl;
    return 0;
}

```


---

