# Longest Subsequence

## 题目描述

You are given array $ a $ with $ n $ elements and the number $ m $ . Consider some subsequence of $ a $ and the value of least common multiple (LCM) of its elements. Denote LCM as $ l $ . Find any longest subsequence of $ a $ with the value $ l<=m $ .

A subsequence of $ a $ is an array we can get by erasing some elements of $ a $ . It is allowed to erase zero or all elements.

The LCM of an empty array equals $ 1 $ .

## 样例 #1

### 输入

```
7 8
6 2 9 2 7 2 3
```

### 输出

```
6 5
1 2 4 6 7
```

## 样例 #2

### 输入

```
6 4
2 2 2 3 3 3
```

### 输出

```
2 3
1 2 3
```

# 题解

## 作者：Leap_Frog (赞：23)

这道题是一道比较友善的数论题。  

### Problem.
大概就是让你从一个集合中选尽可能多的数$a_1...a_n$，满足$\text{lcm}(a_1,...,a_n)\le m$。  

### Solution.
首先，我们发现$a\le\text{lcm}(a,b)$，所以那些$a_i\ge m$的直接可以删掉，我们成功把$a_i$的范围优化成了$10^6$。  

然后，我们可以对于上面那个柿子，把$\text{lcm}$当做被枚举对象。  
这样的话就可以枚举$\text{lcm}$，然后判断每个$a_i$是否可以被取到。  
这样貌似可行，但是可惜复杂度不对，是$n\times m$的。  

接下来，我们考虑像埃氏筛那样去搞。  
就是首先先用一个$ans_i$表示当$\text{lcm}$等于$i$时的最多的数的个数。  
然后，每个位置会对它的所有倍数增加$1$的贡献。  
这样复杂度和埃氏筛一样是$10^6\times log10^6$的，可过。  

具体实现时可以把这些数放进一个桶里，可以减少代码的常数。  

如果还不懂可以看代码注释。  
### Coding.
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,nn,maxnum,maxlcm,a[1000005],b[1000005],cnt[1000005],ans[1000005];
int main()
{
	scanf("%d%d",&n,&m),memset(cnt,0,sizeof(cnt));//读入并清空桶
	for(int i=1;i<=n;i++) scanf("%d",a+i),b[i]=a[i];//b数组接下来要排序、去重一下，方便处理用的。
	for(int i=1;i<=n;i++) if(a[i]<=m) ++cnt[a[i]];//放入桶里。
	sort(b+1,b+n+1),nn=unique(b+1,b+n+1)-b-1,maxnum=-1;//对b数组排序、去重。
	for(int i=1;i<=nn&&b[i]<=m;i++) for(int j=b[i];j<=m;j+=b[i]) ans[j]+=cnt[b[i]];//之前提到过的类似于埃氏筛的东西
	for(int i=1;i<=m;i++) if(maxnum<ans[i]) maxnum=ans[i],maxlcm=i;//统计答案
	printf("%d %d\n",maxlcm,maxnum);//输出第一行
	for(int i=1;i<=n;i++) if(maxlcm%a[i]==0) printf("%d ",i);//如果能取就带上。（注意这里是输出答案的位置，不是输出答案的值。
	return puts(""),0;//完结撒花
}
```
~~无耻求赞~~

---

## 作者：pengyule (赞：11)

这是一篇很啰嗦、很细致的题解，补全了其他题解中说的不是那么清楚的地方。更欢迎大家提意见，我们一起修改完善。

## 题意简述
有一个数组 $a$，从中选出尽可能多的数，使得这些数的最小公倍数不超过一个给定的数 $m$。如果有多种选择，输出任意一种即可。输出格式为，在第一排输出最小公倍数和选出数的数量，在第二排递增地输出选出的数的下标。

## 解法分析
拿到这道题，我们可能束手无策。不妨想一想，对于一种选择，记这些数的最小公倍数为 $lcm$，那么所有选出的数应该都是 $lcm$ 的因数。我们可能会想，是不是暴力枚举 $lcm$ 的值，然后看一看数列中有多少个数能够被枚举到的 $lcm$ 整除，记为 $res$，最后对所有的 $res$ 取一个最大值得到最多可以选多少个数。其实这个复杂度是很高的，为 $O(n\cdot m)$。

对于我们可以转换一个方向，因为一个数被选中则是 $lcm$ 的因数，所以把每一个数都应该融入它的所有在 $m$ 以内的倍数的选数范围。因此对于序列中的每一个数我们只需要把他的所有倍数的答案都加上 $1$，也就是说如果记 $lcm=x$ 时最多可以选 $res_x$ 个数，那么对于 $\underset{1\le i\le n}{a_i}$，将所有满足 $k\times a_i\leq m$ 的 $res_{k\times a_i}\gets res_{k\times a_i}+1$。最后统计一下，哪一个 $res$ 最多。

我们发现这样写是会超时的。我们发现，如果一个数出现多次，那么每次都要大费周折去枚举他的所有倍数，所以我们可以一次性把 $res_{k\times a_i}$ 加 $cnt_{a_i}$，其中 $cnt_{a_i}$ 代表序列 $a$ 中 $a_i$ 的出现次数。然后把 $a_i$ 标记，以后不再管它。

可是有一个问题，就是 $a_i\leq 10^9$ 这个太大了。我们发现，既然 $lcm$ 都要小于 $m$ 那么那些大于 $m$ 的 $a_i$ 肯定是废物啦！对于这种我们直接装作没看见就完事了。 

于是我们愉快地用 $O(m\log m)$ 的复杂度通过了本题。（建议不要用 cin，太慢）

## 代码
```
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int a[N],res[N],cnt[N],book[N];
//a:原数组 res:答案数组 cnt:出现次数 book:标记不用管的a[i]
int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]<=m) cnt[a[i]]++; //只管不大于m的数
	}
	for(int i=1;i<=n;i++){
		if(a[i]>m || book[a[i]]) continue;//大于m的或者已经处理过的
		for(int j=1;a[i]*j<=m;j++)//j枚举是a[i]的多少倍，lcm不能超过m
			res[a[i]*j]+=cnt[a[i]];
		book[a[i]]=1;
	}
	int lcm=1,ans=0;
	for(int i=1;i<=m;i++) 
		if(ans<res[i]) //取最大值，同时把lcm算一下
			ans=res[i],lcm=i;
	printf("%d %d\n",lcm,ans);
	for(int i=1;i<=n;i++)
		if(lcm%a[i]==0) //最终的lcm都已经算好了，那么所有可以被他整除的a[i]都应该要选
			printf("%d ",i);
	return 0;
} 
```

---

## 作者：He_Ren (赞：11)

比赛的时候一开始把题意理解错了，以为子序列是连续的（并没有认真读题），然后想了好半天，后来又读了一遍题才发现自己理解错了

**题目做不出来时，不妨认真多读几遍题**

首先，$a_i\leq 10^9$的数据范围比较难突破

发现所有$a_i > m$可以直接省略，所以$a_i$的范围就缩小到了$10^6$

**范围较大时，可以先尝试缩小数据范围**

然后又卡住了

**不妨转换思考方向**

即，以$a$为主语，条件较多，但以$\text{LCM}$为主语，就简单很多

考虑枚举$\text{LCM}$，然后计算序列长度

但是这样是$O(nm)$的，肯定不行

用$cnt_i$表示数$i$出现的次数，枚举$i$的所有倍数，将那个倍数的答案加上$cnt_i$

这样的复杂度看起来是$m^2$的，这也是一些人不敢写的原因

**正确计算复杂度也是解题中重要的步骤**

发现复杂度其实是$O(\frac{m}{1}+\frac{m}{2}+ \cdots +\frac{m}{m})=O(m\log m)$的，于是可以放心写了

```cpp
#include<cstdio>
#include<algorithm>
const int MAXN = 1e6 + 5;
const int MAXM = 1e6 + 5;
using namespace std;
 
int a[MAXN],b[MAXN],cnt[MAXM],t[MAXM];
 
int main(void)
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; ++i)
		scanf("%d",&a[i]), b[i]=a[i];
	
	for(int i=1; i<=n; ++i)
		if(a[i]<=m) ++cnt[a[i]];
	
	sort(b+1,b+n+1);
	int p = unique(b+1,b+n+1)-b-1;
	
	for(int i=1; i<=p && b[i]<=m; ++i)
	{
		int x=b[i];
		for(int j=x; j<=m; j+=x)
		{
			t[j]+=cnt[x];
		}
	}
	
	int ans=t[1], maxt=1;
	for(int i=2; i<=m; ++i)
		if(t[i]>ans)
		{
			ans=t[i];
			maxt=i;
		}
	
	printf("%d %d\n",maxt,ans);
	for(int i=1; i<=n; ++i)
		if(maxt%a[i]==0) printf("%d ",i);
	return 0;
}
```


---

## 作者：Mine_King (赞：8)

在[此处](https://www.luogu.com.cn/blog/195331/)阅读体验更佳。

AC人生中第一道黑题，写篇题解纪念一下。

题目描述很简洁，题意应该都清楚了。下面来讲一下思路。首先，很明显的一点是如果有$x$个数，这些数都是$k$的约数，那么他们的最小公倍数一定不会大于$k$。那么对于每个$1 \le i \le m$，我们只要找到在$a[]$中有几个她的约数即可。于是有了下面这篇代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,k,lm;
int a[1000005],c[1000005];//a存数量，c存每个数
int lcm(int x,int y){return 1ll*x*y/__gcd(x,y);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		for(int j=1;j*x<=m;j++)
		{
			a[j*x]++;
			if(a[j*x]>a[k]) k=j*x;
		}
	}
	for(int i=1;i<=n;i++)
		if(k%c[i]==0) lm=lcm(lm,c[i]);
	printf("%d %d\n",lm,k);
	for(int i=1;i<=n;i++)
		if(k%c[i]==0) printf("%d ",i);
	return 0;
}
```
结果是，样例都过不去。为什么呢？因为她只是说不会超过k，并不是一定就是k。然后，我们还可以再开一个数组，记录每个[1,m]的在a[]中的约数的最小公倍数，这样就不用在后面多循环一遍了，还有就是可以开一个vector存储用了哪些数，也可以节省时间。于是有了下面这篇代码：
```cpp
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int n,m,k,mx,b[1000005];//存储LCM
vector<int>a[1000005];//存储每个约数
int lcm(int x,int y){return 1ll*x*y/__gcd(x,y);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		for(int j=1;j*x<=m;j++)
		{
			a[j*x].push_back(i);
			if(b[j*x]==0) b[j*x]=1;//初始化b
			b[j*x]=lcm(b[j*x],x);
			if(a[j*x].size()>mx)
				mx=a[j*x].size(),k=j*x;
		}
	}
	printf("%d %d\n",b[k],mx);
	for(int i=0;i<mx;i++) printf("%d ",a[k][i]);
	return 0;
}

```
然后，你挂在了#11。原因是，你没有判断不选任何数的情况，于是最后输出的b[k]成了0而不是1。这里只要加个特判就行了。然后，你又会在#14MLE。根据本人推测，#14全是1，于是你a就会开到$(10^6)^2$，自然就炸了。这里，我们要学会舍去一些东西。我们舍去了vector，选择只存储约数数量，后面再循环输出有哪些数，于是，有了下面这篇代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,k,b[1000005];
int a[1000005],c[1000005];
int lcm(int x,int y){return 1ll*x*y/__gcd(x,y);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		for(int j=1;j*c[i]<=m;j++)
		{
			a[j*c[i]]++;
			if(b[j*c[i]]==0) b[j*c[i]]=1;
			b[j*c[i]]=lcm(b[j*c[i]],c[i]);
			if(a[j*c[i]]>a[k]) k=j*c[i];
		}
	}
	printf("%d %d\n",b[k]==0?1:b[k],a[k]);//特判
	if(k!=0)//特判
		for(int i=1;i<=n;i++)
			if(k%c[i]==0) printf("%d ",i);
	return 0;
}

```
然后，还是在#14，你TLE了。原因很简单，全是1，你的时间复杂度就退化到了O(nm)，自然会炸掉。  

-------下面这个玄学优化不看也没问题-------

我们再加入一个变量f1,存储有多少个1，然后再在最后进行总的处理。由于这个优化很玄学，而且优化后时间复杂度还是会退化到O(nm/2)（即全是2的情况。），在后面的点也会炸掉。所以就不放代码了。不过如果在考场上，这种玄学优化也许可以帮你多拿点分

-------分割线-------

接下来，我们可以发现在原来的基础上改基本不可能了，所以我们要换一个思路——开桶存储。用一个桶存储每个数，大于m的不存储（反正不会用到），然后循环遍历1~m，里面的循环和之前的代码基本一样。这样，最终的时间复杂度最慢也是O(m/1+m/2+m/3+...+m/m)=O(mlogm)。不过这里数组开得比较多，但空间复杂度也只是O(n+3m)而已。  
代码：
```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
int n,m,c[1000005];//c存输入的数
int a[1000005];//ai表示i出现了几次
int k,b[1000005],d[1000005];//b存约数数量，d存LCM
int lcm(int x,int y){return 1ll*x*y/__gcd(x,y);}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&c[i]);
		if(c[i]>m) continue;//大于m的要舍去，1是没用，2是会炸空间
		a[c[i]]++;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j*i<=m;j++)
		{
			b[j*i]+=a[i];//由于总共有ai个，所以不是+1而是+ai
			if(d[j*i]==0) d[j*i]=1;
			d[j*i]=lcm(d[j*i],i);
			if(b[j*i]>b[k]) k=j*i;
		}
	}
	printf("%d %d\n",d[k]==0?1:d[k],b[k]);
	if(k!=0)
		for(int i=1;i<=n;i++)
			if(k%c[i]==0) printf("%d ",i);
	return 0;
}

```
这篇代码亲测可以AC。

---

## 作者：hxhhxh (赞：3)

## 大意

给定一个长度为 $ n $ 的数组 $ a $ 和一个正整数 $ m $ ，求最长的子序列的长度，使得子序列里的最小公倍数不大于 $ d $ 。定义空序列的最大公倍数为 $ 1 $ 。

## 思路

枚举最小公倍数，那么这个子序列的全部元素都应该是最小公倍数的因数。

我们可以类比埃氏筛，将所有 $ a $ 元素的倍数全部的计数器`+1`。但是这样的复杂度有可能达到 $ O(nm) $ 。

考虑优化。将 $ a $ 中所有大于 $ m $ 的元素无视，然后就可以用一个桶来存从 $ 1 $ 到 $ m $ 每一个元素的数量。然后就是 $ O( m \log m + n) $ 的复杂度了。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000006],cnt[1000006],ans=1;
int main(){
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		if(a[i]<=m) cnt[a[i]]++;
	}
	for(int i=m;i>=1;i--) for(int j=i+i;j<=m;j+=i) cnt[j]+=cnt[i];
	for(int i=1;i<=m;i++) if(cnt[ans]<cnt[i]) ans=i;
	printf("%d %d\n",ans,cnt[ans]);
	for(int i=1;i<=n;i++) if(ans%a[i]==0) printf("%d ",i);
	return 0;
}
```

---

## 作者：fsy_juruo (赞：3)

人生第一次A掉Codeforces上的D题，写篇题解纪念一下

题目意思是这样的，给定n个数和一个整数m，从n个数中找出最多的数，使得这些数的最大公约数不大于m

我们设选出来的数都是k的约数，于是可以得到这些数的最小公倍数l一定不大于k
（因为l已经是这些数的最小公倍数，k作为它们的公倍数，不可能比l还小）

所以，我们可以对于1~m中的数，统计给出的数中，有多少个数是它的约数即可。

然后选出最优解。

注意特判一个都不选的情况下，输出“1 0”

AC代码：


	#include<bits/stdc++.h>
	using namespace std;
	template<typename T>void read(T &x){
  	  x=0;int f=1;
  	  char c=getchar();
   	 for(;!isdigit(c);c=getchar()) if(c=='-')f=-1;
   	 for(;isdigit(c);c=getchar()) x=x*10+c-48;
   	 x*=f;
	}
	vector<int> pos[1000010];//数组一定要开大！
	int a[1000010];
	int n,m; 
	int main(){
		read(n); read(m);
		for(int i=1;i<=n;i++){
			read(a[i]);
			if(a[i]<=m){
				pos[a[i]].push_back(i);
			}
		}
		vector<int> cnt(10+m);
		for(int i=1;i<=m;i++){
			for(int j=1;j<=m/i;j++){
				cnt[i*j]+=pos[i].size();//统计约数个数
			}
		}
		int sol=max(1,(int)(max_element(cnt.begin(),cnt.end())-cnt.begin()));
		priority_queue<int,vector<int>,greater<int> > ans;
    	for(int i=1;i<=sol;i++){
       	 if(sol%i==0){
				for(int j=0;j<pos[i].size();j++){
					ans.push(pos[i][j]);
				}
        	}
    	}
    	cout<<sol<<" ";
		if(ans.size()>=1){
    		cout<<ans.size()<<endl<<ans.top(); ans.pop();
		}else{
	    	cout<<0<<endl;
		}
    	while(!ans.empty()){
    		cout<<" "<<ans.top();
    		ans.pop();
		}
		cout<<endl;
		return 0;
	}


时间复杂度$O$ $(n+m+{m}/{2}+{m}/{3}+...+{m}/{m})$ $\approx$ $O$ $(n+m log m)$ , 可以通过所有测试点

(其实特判时多了一个endl，不过不要紧，看不下去的可以删掉）

---

## 作者：XL4453 (赞：2)

### $\text{Difficulty : 2100}$
----
### 解题思路：

一种朴素的想法是对于每一个 $\text{LCM} $ 枚举所有的元素判断是否可行，得到的复杂度是 $O(nm)$，不可以接受。

这时候想到一个非常经典的 $trick$，将枚举因子转化为枚举倍数。也就是反过来思考，对于每一个元素找所有可能的 $\text{LCM}$ 进行更新答案。

实现的时候将所有相同的数放到一起进行更新，计算出答案之后重新找到所有的有贡献数进行输出即可。

注意序列中没有元素的时候的 $\text{LCM}$ 是 $1$ 而不是 $0$。

---
### 代码：
```cpp
#include<cstdio>
using namespace std;
const int MAXN=1000005;
int v[MAXN],n,m,x[MAXN],f[MAXN],maxi=1;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&x[i]);
		if(x[i]>m)continue;
		v[x[i]]++;
	}
	for(int i=1;i<=m;i++)
	for(int j=i;j<=m;j+=i)
	f[j]+=v[i];
	for(int i=1;i<=m;i++){
		if(f[maxi]<f[i])
		maxi=i;
	}
	printf("%d %d\n",maxi,f[maxi]);
	for(int i=1;i<=n;i++)
	if(maxi%x[i]==0)
	printf("%d ",i);
	printf("\n");
	return 0;
}
```


---

## 作者：andyli (赞：1)

设取的所有数都是$k$的约数，则这些数的$~\text{lcm}~$必然不大于$k$。对于$[1,m]$中的每个数，统计$a$中有多少个数是它的约数即可。  

代码如下：  
```cpp
const int maxn = 1000005;

int cnt[maxn];
vector<int> v[maxn];
int main()
{
    int n, m;
    io.read(n, m);
    for (int i = 1; i <= n; i++) {
        int x;
        io.read(x);
        if (x <= m)
            v[x].push_back(i);
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; i * j <= m; j++)
            cnt[i * j] += v[i].size();
    int p = max(int(max_element(cnt + 1, cnt + m + 1) - cnt), 1);
    set<int> ans;
    for (int i = 1; i <= p; i++)
        if (p % i == 0)
            for (auto x : v[i])
                ans.insert(x);
    io.write(p, " ");
    writeln(ans.size());
    bool flag = true;
    for (auto x : ans) {
        if (!flag)
            io.putch(' ');
        flag = false;
        io.write(x);
    }
    if (!ans.empty())
        writeln();
    return 0;
}
```

---

## 作者：Cansanel (赞：1)

人生第一次A黑题QAQ
程序只使用数组，非常直观。解法另一篇题解已经有了，故不多赘述。这里提供一种更简单的代码。
```cpp
#include<algorithm>
#include<cstdio>
const int MAXN = 1e6 + 10;
struct pair{ int x,y; };
int n,m,pt,adr=1,ans1,ans2,a[MAXN],ans[MAXN];
pair c[MAXN];
inline int read(){
	int x=0; char c=0;
	while(c<'0' || c>'9') c=getchar();
	while(c>='0' && c<='9') x=x*10+c-'0',c=getchar();
	return x;
}
bool cmp(pair x,pair y){
	return x.x<y.x;
}
int main(){
	n=read(); m=read();
	for(register int i=1;i<=n;i++){
		c[i].x=read(); c[i].y=i;
	}
	std::sort(c+1,c+n+1,cmp);
	while(adr<=n && c[adr].x<=m){
		pt=1; while(c[adr].x==c[adr+1].x){ adr++; pt++; }
		for(register int i=1;i*c[adr].x<=m;i++)
			a[i*c[adr].x]+=pt;
		adr++;
	}
	for(register int i=1;i<=m;i++)
		if (a[i]>ans2){ ans2=a[i]; ans1=i; }
	printf("%d %d\n",ans1==0?1:ans1,ans2);
	for(register int i=1;i<=n && ans1;i++)
		if (ans1%c[i].x==0) ans[++a[0]]=c[i].y;
	std::sort(ans+1,ans+a[0]+1);
	for(register int i=1;i<=a[0];i++)
		printf("%d ",ans[i]);
	return 0;
}
```
注意输入数据中有很多相同的数，重复处理非常之浪费时间，本人就是因此而T了无数遍QAQ。

---

## 作者：Mobius127 (赞：0)

觉得应该没有 D 的难度 QAQ ？

[题目传送门](https://www.luogu.com.cn/problem/CF632D)

首先我们可以把 $m$ 的数直接扔掉，因为这些数与其他数的 $lcm$ 肯定大于 $m$ 。

然后我们就成功地把 $a$ 的值域缩到了 $1e6$ 级别。

~~然后怎么做呢，枚举还不是超时~~

既然枚举 $a$ 效果不好，我们不妨想想枚举 $lcm$。

我们考虑如何用 $a$ 组成 $lcm$ ，容易想到，某个 $a_i$ 会对 $lcm$ 产生贡献时当且仅当 $a_i|lcm$ ，这样我们就可以枚举每一个 $a_i$ 的倍数，往对应的 $f_u$ 里面加 1 即可。

最后我们找到值最大且下标最小的 $f$ 即为答案。

然后你就发现你超时了（

因为存在重复的 $a_i$ ，所以我们开个桶记录一波就好了，这样复杂度就有了保证。


$O(n\log n+n \ln n)$

### Code:

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#define FALSE return printf("1 0")*0
using namespace std;
typedef long long ll;
const int N=1e6+5; 
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
int n, m, a[N], up;
int f[N], cnt[N];
struct number{
	int v, id;
	bool operator < (const number &A) const{
		return v<A.v;
	}
}num[N];
bool u[N];
signed main(){
	n=read(), m=read();
	for(int i=1; i<=n; i++) a[i]=num[i].v=read(), num[i].id=i;
	sort(num+1, num+n+1);
	for(int i=1; i<=n; i++){
		up=i;
		if(num[i].v>m){up--;break;}
	}
	if(!up) FALSE;
	for(int i=1; i<=up; i++)
		cnt[num[i].v]++;
	for(int i=1; i<=up; i++){
		if(num[i].v==num[i-1].v) continue;
		for(int j=1; j*num[i].v<=m; j++)
			f[j*num[i].v]+=cnt[num[i].v];
	}
	int t=0;f[t]=-1;
	for(int i=1; i<=m; i++) if(f[t]<f[i]) t=i;
	printf("%d %d\n", t, f[t]);
	for(int i=1; i<=up; i++)
		if(t%num[i].v==0&&t>=num[i].v)
			u[num[i].id]=1;
	for(int i=1; i<=n; i++)
		if(u[i])
			printf("%d ", i);
	return 0;
}
```


---

