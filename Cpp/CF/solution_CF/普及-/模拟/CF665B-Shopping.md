# Shopping

## 题目描述

小 $W$​​ 的商店开始了线上购物，线下提货的服务。商店有 $k$​​ 个商品（编号 $1$ 到 $k$）， $n$ 个用户使用了这项服务。每个用户的订单都包含 $m$ 个商品，并在线付费，以  $a_{ij}$ 表示第 $i$ 个用户的订单中第 $j$ 个商品的编号。所有的商品是排成一排的，在小 $W$ 收到第 $i$ 件商品时，他会从前向后找所有的商品 $a_{ij}$  ( $1\le j\le m$ )，令 $pos(x)$ 表示该用户需要的编号为 $x$ 的商品，此时在序列中的位置。小 $W$ 需要 $pos(a_{i1})+pos(a_{i2})+...+pos(a_{im})$ 为第 $i$ 个客户服务的时间。当小 $W$ 访问第 $x$ 个元素时，他会将新的存货放到最前面，并将位置为 $x$ 的元素移除，因此，此序列是在不断更新的。你需要算出小 $W$​ 需要的时间。假设市场上有无尽的存货。

## 样例 #1

### 输入

```
2 2 5
3 4 1 2 5
1 5
3 1
```

### 输出

```
14
```

# 题解

## 作者：_lgh_ (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF665B)

蒟蒻的第一篇题解

## 一道纯粹的模拟题
用 vector 维护，每次 for 循环找到该数，删除并在队首插入即可。答案即为每次操作累加找到数的位置 $+1$。

具体见代码：
```cpp
#include<bits/stdc++.h> //懒人专用 
using namespace std; 
vector<int> vec; //用 vector 维护 
int n,m,k,/*前三个如题目*/Time;//Time 表示用的时间 
int main(){ 
  cin>>n>>m>>k;//输入都会 
  for(int i=1,x;i<=k;i++) cin>>x,vec.push_back(x); //输入并存入vector中 
  for(int i=0,x,wei;i<n;++i)//枚举 
	for(int j=0;j<m;++j){
      cin>>x；
      for(wei=0;wei<vec.size();wei++) 
      if(vec[wei]==x) break;//找到 x 的位置 
      vec.erase(vec.begin()+wei);//删除 
      vec.insert(vec.begin(),x);//在头部插入 
      Time+=wei+1,wei=0; //增加时间，位置清零（回到头部） 
    }  
  cout<<Time<<'\n'；//输出时间
  return 0; 
  }//和谐洛谷，拒绝抄袭

```


---

## 作者：世末OIer (赞：3)

题解：模拟。在当前的序列中查找每一个询问，删除它，然后加入队首即可。

```cpp
int n,m,k;
vector<int> v;
int main(){
	int i,j,f,x,ans=0;
	rdi(n),rdi(m),rdi(k); 
	for(i=0;i<k;++i) rdi(x),v.push_back(x);//按照顺序排队
	for(i=0;i<n;++i){
		for(j=0;j<m;++j){
			rdi(x);
			for(f=0;f<v.size();++f) if(v[f]==x) break;//找到此物品
			v.erase(v.begin()+f);//删除
			v.insert(v.begin(),x);//压入
			ans+=f+1;
		}
	}
	print(ans);
}
```

---

## 作者：wangping (赞：2)

**思路**

题上首先给了三个数 $n,m,k$，然后在第二行里给出了 $k$ 个数，然后又 $n\times m$ 个操作，代表每一次把这个操作的数移动到第一位，其他的往后推，每次移动的时候有一个权值（从第一个数到第这个数的相差的位置数），问的是所有权值的和，数据量不大，直接模拟就好。

**注**

看到楼上用的 `vector`，我这里用数组。

**Code**

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n, m, k, x, ans = 0, a[105];
	scanf("%d %d %d", &n, &m, &k);
	for (register int i(1); i <= k; ++i)
		scanf("%d", &a[i]);
	for (register int i(1); i <= n * m; ++i)
	{
		scanf("%d", &x);
		register int j, l;
		for (j = 1; j <= k; ++j)
			if (a[j] == x)
				break;
		ans += j;
		for (l = j; l >= 2; --l)
			a[l] = a[l - 1];
		a[1] = x;
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：Creative_sad_yosgic (赞：1)

## CF665Bの题解
### 题意
给你长度为 $k$ 的数组和 $n\times m$ 个数组里有的数，每次取一个数在数组后**删除后放在数组最前**，其他数顺次延后，并在修改前的数组找到这个数的**下标**作为花费，求总花费。
### 做法
向大家介绍 **STL-vector**。（了解可跳过）

vector 是 c++ 内置的一种数据结构，与数组类似，也可以将它当作数组使用。

作为 STL 的一种，我们可以使用它很多方便的功能，如

查找数组内元素个数：
```cpp
int l=mp.size();
```

查找数组内的元素位置和删除元素：
```cpp
vector<int>::iterator id=find(mp.begin(),mp.end(),a);//元素a位置迭代器
int ans=id-mp.begin()+1;//元素a位置
mp.erase(id);//数组内删除a元素
  
```
向数组内添加元素：
```cpp
mp.push_back(a);//在数组尾部添元素a
mp.insert(mp.begin()+b,a);//在数组第b个位置添加元素a
mp[b]=a;//修改某位置元素方法与普通数组相同
```
那么这题的方法就显而易见，用 find 找出当前元素所在位置并算出下标，再用 erase 删除该元素，然后 insert 这个元素到队首并累加这个元素之前的下标即可。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> mp;
int n,m,k,a,ans;
int main(){
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		cin>>a;
		mp.push_back(a);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
		cin>>a;
		vector<int>::iterator id=find(mp.begin(),mp.end(),a);
		mp.erase(id);
		mp.insert(mp.begin(),a);
		ans+=id-mp.begin()+1;
	}
	cout<<ans<<'\n';
	return 0;
}
```



---

## 作者：lmndiscyhyzdxss (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF665B)
-----------------------------------------------------------
- ### 先讲讲思路
第一行给了三个数： $ n $, $ m $ ,$ k $ ，然后在第二行里给出了 $ k $ 个数，然后 $ n \times m $ 个操作，每一次把这个要操作的数移动到第一位，其余的往后推，每次移动的时候有一个数值（从第一个数到这个数的相差的位置数），求的是所有数值的和，数据量不大，直接模拟就行。
- ### 接着是代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,x,ans,a[110];
int main()
{
	
    cin>>n>>m>>k;
    for(int i=1;i<=k;i++)cin>>a[i];
    for(int i=1;i<=n*m;i++)
    {
        cin>>b;
        int l,h;
        for(l=1;l<=k;l++)if(a[l]==b)break;
        ans+=l;
        for (h=l;h>=2;h--)a[h]=a[h-1];
        a[1]=b;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：LOVE_Ynoi (赞：1)

# CF665B 题解
### 题目大意
给定 数列 $A$ , 有 $n \times m$ 次操作，对于每一个操作，给定一个数 $x$ ,将 $A_x$ 移动到数列前方， 每次操作的花费为 $x$ ,求进行所有操作后的总花费。  
### 思路
观察到 $n$ 很小，直接模拟即可。  
用数组模拟细节很多，所以这里采用 ``vector`` 来进行求解。  
以下为下文用到的库函数 (均以 ``vector<int> `` 举例) 
1. ``iterator find(iterator begin,iterator end,int x)`` ：寻找x在容器中的位置 (各种容器通用，包括 ``vector`` )
2. ``void insert(iterator pos,int x)`` ： 在指定位置加入 $x$  
3. ``iterator begin()`` ： 返回开头处迭代器。
4. ``void erase(iterator pos)`` 删除指定位置的元素
5. ``void push_back(int x)`` 在最后加入元素  

时间复杂度：$O(n^3)$ ,可以通过。
### 简单的代码：

```c++
#include<bits/stdc++.h>
using namespace std;
vector<int> v;
int n,m,k;
int ans;
int main(){
    cin>>n>>m>>k;
    for(int i = 1;i<=k;i++){
        int x;
        scanf("%d",&x);
        v.push_back(x);
    }
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=m;j++){
            int x;
            scanf("%d",&x);
            int pos = find(v.begin(),v.end(),x)-v.begin();
            ans += (pos+1);
            v.erase(v.begin()+pos);
            v.insert(v.begin(),x);
        }
    }
    printf("%d",ans);
    return 0;
}
```

---

## 作者：togeth1 (赞：0)

## [题 目 传 送 门](https://www.luogu.com.cn/problem/CF665B)

### [题意解析]
给出三个整数 $n$，$m$ 和 $k$，让我们做 $n \times m$ 次操作：

1. 把这个操作的数移动到第一位。

2. 其余的数字往后推一位。

3. 由于每次移动的时候有一个**第一个数到第这个数的相差的值**。 

让我们求所有移动的值的总和。

### [思路分析]
我们看一眼数据范围 $n,k\leq100$，$1\leq m\leq k$，也就是说，直接模拟 $n \times m$ 次并不会超时。所以我们可以直接模拟 $n \times m$ 次操作过程，统计**值**的和就好了。

这里提一下后推一位的操作，就是把原来第 $i$ 个数 $a_i$，移到第 $i-1$ 的位置，一直**倒推**。

### [贴上代码]
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,a[1010],ans;
int main()
{
	cin>>n>>m>>k;
	for(int i=1; i<=k; i++)cin>>a[i];
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			/*注：是n ×m次操作*/
			int t,pos;
			cin>>t; 
			for(int p=1; p<=k; p++)if(a[p]==t){ans+=p;pos=p;break;}
			/*统计值的和，记录位置，直接退出*/
			for(int p=pos; p>=2; p--)a[p]=a[p-1];
			a[1]=t;
			/*注意要记得处理第一个！！*/
		}
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：yyyymh (赞：0)

#### 题意

给定一个数列，每次询问一个数字在这个序列中的位置并在完成操作后将这个数字移到数列最前面，最终输出这些位置的和。

#### 分析问题

这道题是一道较为容易的模拟，数据范围较小。对于每次询问暴力枚举，进行对比，相同的话就将这个数移到最前面并结束这次询问，定义一个变量存储这些位置的和。

#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105];
int main(){
	int n,m,k,t,x;
	long long sum=0;
	cin>>n>>m>>k;
	for(int i=1;i<=k;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			scanf("%d",&x);
			for(int l=1;l<=k;l++){
				if(a[l]==x){
					sum+=l;
					t=a[l];
					for(int o=l;o>=2;o--){
						a[o]=a[o-1];
					}
					a[1]=t;
					break;
				}
			}
		}
	}
	printf("%lld",sum);
	return 0;
}
```





---

## 作者：Federico2903 (赞：0)

# 模拟好题
## 题意
看描述确实有点懵，但是看下样例解释就明白了。  
从一个数组中找一个数，把它丢到最前面，ans 累加位置即可。  
题意很简单明了，vector 维护数组即可。  
注：vector 数组下标从零开始，所以累加位置要**加一**。  
更多看代码注释。  
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> arr;//定义vector数组
int main() {
	int n,m,k;
	cin >> n >> m >> k;
	for(int i=0;i<k;i++){
		int t;
		cin >> t;
		arr.push_back(t);//把输入的数丢进vector数组末尾
	}
	int ans=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			int t;
			cin >> t;
			for(vector<int>::iterator iter=arr.begin();iter<=arr.end();iter++){//这里初始化了个迭代器，和指针类似，可以通过自加来访问下一个元素，通过前加*号来取值
				if((*iter)==t){//如果相同
					ans+=iter-arr.begin()+1;//累加，下标从0开始
					arr.erase(arr.begin()+(iter-arr.begin()),arr.begin()+(iter-arr.begin())+1);//擦除那个数，erase操作不包含第二个参数指向的值，只清除到指定的结束点的前一个，所以这里加一
					arr.insert(arr.begin(),t);//插入进头部
				}
			}
		}
	}
	cout << ans;//输出
}
```

---

## 作者：Steven_lzx (赞：0)

## 思路

**模拟**，我们用 STL 的 vector，操作时暴力找到元素所在位置，erase 后将其 insert 到开头。

## 关键代码

```cpp
for(int i=0;i<n;i++)
{
	for(int j=0;j<m;j++)
	{
		x=fastio_read();
		for(l=0;l<p.size();l++)
		{
			if(p[l]==x)
			{
				break;
			}
		}
		p.erase(p.begin()+l);
		p.insert(p.begin(),x);
		ans+=l+1;
	}
}
```


---

