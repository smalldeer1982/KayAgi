# Array

## 题目描述

Vitaly has an array of $ n $ distinct integers. Vitaly wants to divide this array into three non-empty sets so as the following conditions hold:

1. The product of all numbers in the first set is less than zero $ (<0) $ .
2. The product of all numbers in the second set is greater than zero $ (>0) $ .
3. The product of all numbers in the third set is equal to zero.
4. Each number from the initial array must occur in exactly one set.

Help Vitaly. Divide the given array.

## 样例 #1

### 输入

```
3
-1 2 0
```

### 输出

```
1 -1
1 2
1 0
```

## 样例 #2

### 输入

```
4
-1 -2 -3 0
```

### 输出

```
1 -1
2 -3 -2
1 0
```

# 题解

## 作者：Kdlyh (赞：7)

 这是一个结论题，大概入门难度吧，不知道怎么就成蓝题了。。。
 
 注:设第一个集合的乘积为a,第二个集合的乘积为b,第三个集合的乘积为c。

只要你有初中文化水平，就可以知道——**任何数乘零皆得零**

~~这不就是个签到题了么~~所以呢?

先读入每一个数，然后开两个数组，一个存正数，一个存负数。

### 我们先考虑这$n$个数中有正数也有负数的情况
- 开始处理a的值，为了尽量简化代码，直接凑一个负数就行了，所以把负数数组的第一个放到第一个集合里，完毕.
- 然后开始处理b的值,同样为了尽量简化代码，直接把正数数组的第一个放到第二个集合里，完毕.
- 然后再把剩下的第二个到最后一个的正数和负数全部和$0$放在一起,于是——$c==0$。完事了。。。
### 再考虑下这$n$个数中只有负数和$0$的情况
- 其实与第一种情况大致相同，只不过凑正数时要用两个负数(负负得正的思想)就行了。
### 至于只有正数的情况
- 因为题目保证有解，只有正数是永远也乘不出负数的，该情况不存在

#### 代码实现太简单了，建议读者们理解了自己写出来。在这里就不放了

---

## 作者：yangyuanxi44 (赞：4)

## 1.题目大意：

  将一串数放入三个集合中，第一个乘积小于0，第二个乘积大于0，第三个乘积等于0。
  
  
## 2.思路：
整体上说这道题不难，只需明白数的**乘积规律**和**分类思路**，就十分简单。

### ①分类思路：
   为正数是否为0来判断（最显著的特点）,详解见下文
### ②处理负数：
（1）当负数有奇数个时，其乘积为奇数（那我们就可以不用管了，直接放到第一个集合中即可）

eg：$(-1)^3=-1$

（2）当负数有偶数个时，其乘积为偶数

eg：$(-1)^2=1$

那么多出来的一个丢到$0$那里即可（$0$乘任何数为$0$），就可以保持负数有奇数个了

### ③处理正数：
（1）正数乘多少个皆为正数

（2）正数个数有可能为$0$的情况 ，所以这个时候需要两个负数，其乘积才为正数，而偶数不改变奇偶性（奇数$±$偶数$=$奇数，偶数$±$偶数$=$偶数）所以，负数仍为奇数个(为偶数个的话丢到$0$那里)

 注：负数个数不可能为0，因为正数乘多少个皆为正数~~
 
###   ④处理0：
 （1）见上文操作
 
 （2）出现$0$就放到第三个集合，因为$0$乘任何数皆为$0$


 好了，现在我们就可以实现代码了~~冲！！！

# 3.代码实现：
代码不难，$\color{red} \text{理解}$便可轻松打出：

```cpp
#include<bits/stdc++.h>
using namespace std;
int z[105],f[105];//正数数组，负数数组 
int lcnt,zt,ft;// 0数量，正数数量，负数数量 
int n;//数字个数 
int main(){
	cin>>n;
	for(int i=1 ; i<=n ; i++){
		int x;
		cin>>x;//输入每个数 
		if(x>0){//为正数 
		    zt++;//正数数量++
			z[zt]=x;//存入正数数组 
		}else if(x<0){//为负数
		    ft++;//负数数量++ 
			f[ft]=x;//存入负数数组 
		}else{//为0 
			lcnt++;//0数量++
		}
	} 
	if(zt!=0){//正数数量不为0 
		int lf,pd=0;//要丢到0那里的数，判断负数个数奇偶 
		if(ft%2!=0){//为奇数
			pd=0;
			cout<<ft<<" ";//输出负数数量 
			for(int i=1 ; i<=ft ; i++) cout<<f[i]<<" ";//输出负数
			cout<<endl;
		}if(ft%2==0){//为偶数
			pd=1;//为偶数 
			cout<<ft-1<<" ";////输出负数数量-1，因为要丢出去到0有1个 
			for(int i=1 ; i<=ft-1 ; i++) cout<<f[i]<<" ";//输出负数
			lf=f[ft];//丢出去到0的数 
			cout<<endl;
		}
		cout<<zt<<" ";
		for(int i=1 ; i<=zt ; i++) cout<<z[i]<<" ";//输出正数
		cout<<endl;
		if(pd==0){//负数个数为奇数（不用丢过来） 
			cout<<lcnt<<" ";//输出0个数 
			for(int i=1 ; i<=lcnt ; i++) cout<<0<<" ";//输出0
		}
		if(pd==1){//负数个数为偶数（需要丢过来） 
			cout<<lcnt+1<<" ";//输出0个数+1（有丢过来的） 
			for(int i=1 ; i<=lcnt ; i++) cout<<0<<" ";
			cout<<lf;
		}
	}	
	if(zt==0){//正数数量为0 
		int zf1,zf2,lf,pd;//要给正数补上的两个数 
		if(ft%2!=0){
			pd=0;
			cout<<ft-2<<" ";//输出负数数量（有给正数补的数，ft-2） 
			for(int i=1 ; i<=ft-2 ; i++) cout<<f[i]<<" ";
			cout<<endl;
			zf1=f[ft-1];//给正数补上的两个数 
			zf2=f[ft];//给正数补上的两个数 
		}
		if(ft%2==0){//同上 
			pd=1;
			cout<<ft-3<<" ";
			for(int i=1 ; i<=ft-3 ; i++) cout<<f[i]<<" ";
			cout<<endl;
			zf1=f[ft-2];
			zf2=f[ft-1];
			lf=f[ft];
		}
		cout<<2<<" "<<zf1<<" "<<zf2<<endl;//给正数补的两个数 
		if(pd==0){//同上 
			cout<<lcnt<<" ";
			for(int i=1 ; i<=lcnt ; i++) cout<<0<<" ";
		}
		if(pd==1){//同上
			cout<<lcnt+1<<" ";
			for(int i=1 ; i<=lcnt ; i++) cout<<0<<" ";
			cout<<lf;
		}
	}
	return 0;
} 
```
# 4，后话：
感谢辛苦的管理员的审核，也感谢大家的支持，也可提出宝贵建议谢谢。

### 谢谢大家

## 理解最重要!!!



---

## 作者：Yanrqin (赞：4)

第一次写题解

~~同学思想~~

要使第一个集合乘积为负数，应放奇数个。~~索性~~不如只放一个。

第二个集合乘积要为正数，放两个，或不放。

**注意**（要将所有正数放在第二个，当没有足够两个的时候，集合乘积就还是正数）

剩下的全部塞进第三个（其中有0，乘积必为0）

```cpp
#include<iostream>
using namespace std;
int n,a[101],b[101],c[101],A,B,C,n1[101],n2[101],n3[101],N1,N2,N3,k;
//a,b,c数组分别存正负数和零
int main(){
    cin>>n;int i;
    for(i=1;i<=n;i++){
        cin>>k;
        if(k>0){
            a[A]=k;A++;continue;
        }
        else if(k<0){
            c[C]=k;C++;continue;
        }
        else {
            b[B]=k;B++;continue;
        }
    }
    for(i=0;i<A;i++){
        n2[N2]=a[i];N2++;
    }
    for(i=0;i<B;i++){
        n3[N3]=b[i];N3++;
    }
    n1[N1]=c[0];N1++;
    //判断够不够放
    if(C>=3){
        n2[N2]=c[1];N2++;n2[N2]=c[2];N2++;
        for(i=3;i<C;i++){
            n3[N3]=c[i];N3++;
        }
    }
    //不够就这样做
    else {
        for(i=1;i<C;i++){
            n3[N3]=c[i];N3++;
        }
    }
    cout<<N1<<" ";
    for(i=0;i<N1;i++){
        cout<<n1[i]<<" ";}
    cout<<endl<<N2<<" ";
    for(i=0;i<N2;i++){
        cout<<n2[i]<<" ";}
    cout<<endl<<N3<<" ";
    for(i=0;i<N3;i++){
        cout<<n3[i]<<" ";}
        return 0;
}
```

---

## 作者：xiaoPanda (赞：3)

### Problem
把一个 $n$ 个元素的序列放进三个集合中，满足以下条件：

1. 第一个集合里所有元素的乘积小于 $0$

2. 第二个集合里所有元素的乘积大于 $0$
 
3. 第三个集合里所有元素的乘积等于 $0$

求一个满足条件的方案。

### Solution
很明显 $0$ 乘以任何数都得 $0$，所以第三个集合只要有 $0$ 即可，其他数无所谓。

根据小学学的负数乘法，负负得正，负正得负。

所以第一个集合里要有奇数个负数，第二个集合里要有偶数个负数。

因为只要一个满足条件的方案，所以只在第一个集合里放 $1$ 个负数，在第二个集合里放 $2$ 个负数（当然如果输入的数据中负数不够那只能放一个正数），其他数放在第三个集合中（反正乘积是 $0$ 没有影响）。
### Code
```cpp
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i], sum += a[i] < 0;//预处理出有多少个负数
	for (int i = 1; i <= n; i++) {
		if (a[i] < 0) {
			if (tot1 == 0)ans1[++tot1] = a[i];//第一个集合中至少要有1个负数
			else {
				if (tot2 < 2 && sum >= 3)//要有足够的负数
					ans2[++tot2] = a[i];//第二个集合中至少要有2个负数
				else ans3[++tot3] = a[i];//多余的数放在第三个集合中
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (a[i] > 0) {
			if (tot2 < 2)ans2[++tot2] = a[i];//如果负数不够只能放正数
			else ans3[++tot3] = a[i];
		}
		if (a[i] == 0)
			ans3[++tot3] = a[i];//多余的数放在第三个集合中
	}
	cout << tot1 << " ";
	for (int i = 1; i <= tot1; i++)
		cout << ans1[i] << " ";
	cout << endl;
	cout << tot2 << " ";
	for (int i = 1; i <= tot2; i++)
		cout << ans2[i] << " ";
	cout << endl;
	cout << tot3 << " ";
	for (int i = 1; i <= tot3; i++)
		cout << ans3[i] << " ";
	cout << endl;//输出答案
```


---

## 作者：Fat_Fish (赞：2)

**思路：**

**第一种操作：** 从头开始扫描到第一个负数，输出即可

**第二种操作：** 从头开始扫描第一个正数，输出，否则寻找两个负数，负负得正，输出即可。

**第三种操作：** 将剩下的数全丢进最后一个数列，输出即可

Code:
```cpp
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int a[105];
bool k[105];
int main(){
	int n;
	cin>>n;
	int sx=n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		if(a[i]<0) {
			cout<<1<<' '<<a[i]<<'\n';
			k[i]=true;
			--sx;
			break;
		}
	}
	bool s=true;
	for(int i=1;i<=n;++i){
		if(a[i]>0){
			cout<<1<<' '<<a[i]<<'\n';
			k[i]=true;
			s=false;
			--sx;
			break;
		}
	}
	if(s){
		int sum=0;
		cout<<2<<' ';
		for(int i=1;i<=n;++i){
			if(sum==2){
				cout<<"\n";
				break;
			}
			if(a[i]<0&&!k[i]){
				cout<<a[i]<<' ';
				++sum;
				k[i]=true;
			}
		}
		sx-=2;
	}
	cout<<sx<<' ';
	for(int i=1;i<=n;++i){
		if(!k[i]){
			cout<<a[i]<<' ';
		}
	}
	cout<<'\n';
	return 0;
}
```


---

## 作者：xukaiyi_kaiyi (赞：0)

# 我的思路
既然题目都说明了是集合，那为啥不用STL大法呢？
```cpp
include<set>
```
# 正题
## 算法思路
算法思路题解区已经有很多了，不再细讲，我这里采取这样的方法：
		
     1.将将给出集合中的数分成正数，零，负数三部分；
     2.如果没有正数，就从负数集合移两个过来；
     3.如果负数集合中有偶数个负数，就移一个到零集合。

我认为这个方法用STL执行时最方便，也最好理解。
## 分段代码
准备工作：
```cpp
#include<iostream>
#include<set>
using namespace std;
set<int> a;//原始数组
set<int> p;//正数集合
set<int> u;//负数集合
set<int> z;//零集合
int n;//元素个数
int t;//临时变量
```

输入部分：
```cpp
cin>>n;//输入n
for(int i=0;i<n;i++){//循环输入
	cin>>t;//输入
	a.insert(t);//插入a集合
}
```
1.将将给出集合中的数分成正数，零，负数三部分：
```cpp
set<int>::iterator it;//定义一个迭代器
for(it=a.begin();*it<0;it++){//因为set是排好序的，所以直接遍历
    u.insert(*it);//最前面的是负数
}
for(;*it==0;it++){
    z.insert(*it);//然后是零
}
for(;it!=a.end();it++){
    p.insert(*it);//最后是正数
}
```
2.如果没有正数，就从负数集合移两个过来:
```cpp
it=u.begin();//迭代器初始化到负数集合的开头
if(p.size()==0){//如果没有正数
    for(int i=0;i<2;i++){//把两个负数集合的数移到正数集合
        p.insert(*it);//向正数集合中插入负数集合的数
        u.erase(it++);//删掉原来负数集合中的数
    }
}
```
3.如果负数集合中有偶数个负数，就移一个到零集合:
```cpp
if(u.size()%2==0){//如果负数集合中有偶数个数
    z.insert(*it);//向零集合中插入一个负数集合中的数
    u.erase(*it);//删掉原来负数集合中的数
}
```
输出部分：
```cpp
cout<<u.size();//输出负数集合的大小
for(it=u.begin();it!=u.end();it++){
    cout<<' '<<*it;//输出每一个数
}
cout<<endl<<p.size();//输出正数集合的大小
for(it=p.begin();it!=p.end();it++){
    cout<<' '<<*it;//输出每一个数
}
cout<<endl<<z.size();//输出零集合的大小
for(it=z.begin();it!=z.end();it++){
    cout<<' '<<*it;//输出每一个数
}
```
完结撒花：
```cpp
return 0;
```
最后放上完整代码：
```cpp
#include<iostream>
#include<set>
using namespace std;
set<int> a;//原始数组
set<int> p;//正数集合
set<int> u;//负数集合
set<int> z;//零集合
int n;//元素个数
int t;//临时变量
signed main(){//主函数
    cin>>n;//输入n
    for(int i=0;i<n;i++){//循环输入
        cin>>t;//输入
        a.insert(t);//插入a集合
    }
    set<int>::iterator it;//定义一个迭代器
    for(it=a.begin();*it<0;it++){//因为set是排好序的，所以直接遍历
        u.insert(*it);//最前面的是负数
    }
    for(;*it==0;it++){
        z.insert(*it);//然后是零
    }
    for(;it!=a.end();it++){
        p.insert(*it);//最后是正数
    }
    it=u.begin();//迭代器初始化到负数集合的开头
    if(p.size()==0){//如果没有正数
        for(int i=0;i<2;i++){//把两个负数集合的数移到正数集合
            p.insert(*it);//向正数集合中插入负数集合的数
            u.erase(it++);//删掉原来负数集合中的数
        }
    }
    if(u.size()%2==0){//如果负数集合中有偶数个数
        z.insert(*it);//向零集合中插入一个负数集合中的数
        u.erase(*it);//删掉原来负数集合中的数
    }
    cout<<u.size();//输出负数集合的大小
    for(it=u.begin();it!=u.end();it++){
        cout<<' '<<*it;//输出每一个数
    }
    cout<<endl<<p.size();//输出正数集合的大小
    for(it=p.begin();it!=p.end();it++){
        cout<<' '<<*it;//输出每一个数
    }
    cout<<endl<<z.size();//输出零集合的大小
    for(it=z.begin();it!=z.end();it++){
        cout<<' '<<*it;//输出每一个数
    }
    return 0;
}
```





---

## 作者：BreakPlus (赞：0)

## [$\color{blue} \text{CF300A Array}$](https://www.luogu.com.cn/problem/CF300A)

### $\text{Discribe}$

把一个数组分成三组，第一组数之积 $< 0$,第二组数之积 $> 0$，第三组数之积 $=0$ 。

### $\text{Solution}$

我们先把所有 $0$ 放在第三个集合，然后把一个负数放在第一个集合。

对于第二个集合，先把剩余的数都放进去，如果发现乘积为负，则把一个负数放在第三个集合。

这样就可以满足条件了。

### $\text{Code}$

```cpp
#include<cstdio>
#include<vector>
using namespace std;
int n,a[110],now=1;
vector<int>v1,v2,v3;
bool vis[110];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++){
		if(a[i]==0) v3.push_back(0),vis[i]=true;
		else{
			if(a[i]<0) now*=(-1); 
		}
	}
	if(now==1){
		for(int i=1;i<=n;i++)
			if(a[i]<0){
				v3.push_back(a[i]);
				vis[i]=true;
				break;
			}
	}
	for(int i=1;i<=n;i++)
		if(a[i]<0 && (!vis[i])){
			v1.push_back(a[i]);
			vis[i]=true;
			break;
		}
	for(int i=1;i<=n;i++)
		if(!vis[i]) v2.push_back(a[i]);
	printf("%d ",v1.size());
	for(int i=0;i<v1.size();i++) printf("%d ",v1[i]); puts("");
	printf("%d ",v2.size());
	for(int i=0;i<v2.size();i++) printf("%d ",v2[i]); puts("");
	printf("%d ",v3.size());
	for(int i=0;i<v3.size();i++) printf("%d ",v3[i]); puts("");
	return 0;
}
```

---

## 作者：fls233666 (赞：0)

为了方便下文描述，我们把元素乘积为负数的集合称为集合 $0$，把元素乘积为正数的集合称为集合 $1$，把元素乘积为零的集合称为集合 $2$。

根据集合的定义，我们首先把读入的负数都放到集合 $0$ 中，把读入的正数全部放到集合 $1$ 中，把全部的 $0$ 放到集合 $2$ 中。这样放完之后，我们考虑现在会出现什么样的不符合要求的情况。容易发现有以下两种情况：

- 正数集合为空【没有正数】
- 负数有偶数个【集合 $0$ 乘积为正数】

对于没有正数的情况，我们从集合 $0$ 中取出两个负数放到集合 $1$ 中，因为负数与负数相乘得到正数，没有正数的问题就解决了。

对于负数有偶数个的情况，我们从集合 $0$ 中取出一个负数，放到集合 $2$ 中。因为 $0$ 与任何数相乘都得 $0$，所以集合 $2$ 仍然满足要求。同时，因为集合 $0$ 去除了一个负数，集合 $0$ 也得以满足要求。

最后，因为原版英文题目中保证存在解，因此不需要另行判断每一步的操作是否可行。按照上述思路实现代码即可得到满分。

代码如下：

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#define ll long long
#define rgt register int
using namespace std;

int n,num;
vector <int> st[3];

int main(){
	scanf("%d",&n);
    
	for(rgt i=1;i<=n;i++){
		scanf("%d",&num);
		if(num<0)  //负数放入集合0
			st[0].push_back(num);
		if(num>0)  //正数放入集合1
			st[1].push_back(num);
		if(num==0) //0放入集合2
			st[2].push_back(num);
	}  //读入并初步处理数据
    
	if(st[1].empty()){
		st[1].push_back(st[0][st[0].size()-1]);
		st[0].pop_back();
		st[1].push_back(st[0][st[0].size()-1]);
		st[0].pop_back();
	} //处理没有正数的情况
    
	if(st[0].size()%2==0){
		st[2].push_back(st[0][st[0].size()-1]);
		st[0].pop_back();
	} //处理负数有偶数个的情况
    
	printf("%d ",st[0].size());
	for(rgt i=0;i<st[0].size();i++)
		printf("%d ",st[0][i]);
	printf("\n");
	printf("%d ",st[1].size());
	for(rgt i=0;i<st[1].size();i++)
		printf("%d ",st[1][i]);
	printf("\n");
	printf("%d ",st[2].size());
	for(rgt i=0;i<st[2].size();i++)
		printf("%d ",st[2][i]);
	printf("\n");
   //输出每个集合的元素
    
	return 0;
}

```


---

## 作者：rui_er (赞：0)

求一个满足条件的方案即可，显然直接构造。

根据常识，可以列出下表：

|乘数|+|0|-|
|:-:|:-:|:-:|:-:|
|+|+|0|-|
|0|0|0|0|
|-|-|0|+|

发现正数的情况有两种，需要分类；负数比较简单，只有一种（正数乘负数）；任何数乘 $0$ 都为 $0$。所以我们可以先讨论正数，然后构造负数，最后把没用的都扔到 $0$ 里面就可以。

如果输入有正数，可以取一个正数单独在正数堆，取一个负数单独在负数堆，剩下的都扔到 $0$ 堆，显然符合条件；如果输入没有正数，可以取两个负数相乘在正数堆，取一个负数在负数堆，剩下的都扔到 $0$ 堆，也符合条件。

参考代码：

```cpp
//By: Luogu@rui_er(122461)
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=y;x<=z;x++)
#define per(x,y,z) for(int x=y;x>=z;x--)
#define debug printf("Running %s on line %d...\n",__FUNCTION__,__LINE__)
using namespace std;
typedef long long ll;
const int N = 105; 

int n, a[N];
template<typename T> void chkmin(T &x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T &x, T y) {if(x < y) x = y;}
vector<int> nega, posi, zero, x, y, z;
void print(const vector<int> &p) {
	int sz = p.size();
	printf("%d ", sz);
	rep(i, 0, sz-1) printf("%d%c", p[i], " \n"[i==sz-1]);
}

int main() {
	scanf("%d", &n);
	rep(i, 1, n) {
		scanf("%d", &a[i]);
		if(a[i] > 0) posi.push_back(a[i]);
		else if(a[i] < 0) nega.push_back(a[i]);
		else zero.push_back(a[i]);
	}
	if(posi.size()) {
		y.push_back(posi[0]);
		x.push_back(nega[0]);
		int sz = 0;
		sz = nega.size(); rep(i, 1, sz-1) z.push_back(nega[i]);
		sz = posi.size(); rep(i, 1, sz-1) z.push_back(posi[i]);
		sz = zero.size(); rep(i, 0, sz-1) z.push_back(zero[i]);
	}
	else {
		y.push_back(nega[0]);
		y.push_back(nega[1]);
		x.push_back(nega[2]);
		int sz = 0;
		sz = nega.size(); rep(i, 3, sz-1) z.push_back(nega[i]);
		sz = zero.size(); rep(i, 0, sz-1) z.push_back(zero[i]);
	}
	print(x); print(y); print(z);
	return 0;
}
```

---

## 作者：_Scaley (赞：0)

这是一道分类题

## 题意概要：

有一个长度为 n 的序列，里面有 n 个元素，把这 n 个元素分成三个集合：

第一个集合要求所有元素的乘积为负；

第二个集合要求所有元素的乘积为正；

第三个集合要求所有元素的乘积为 0；

## 题目分析：

### 可以对每个集合进行分析：

* 第一个集合：

既然要求所有元素的乘积为负，只要整个集合的元素中的负数的个数为奇数，那整个集合的元素乘积为负。

所以可以让这个集合只有一个元素：一个负数。

* 第二个集合：

既然要求所有元素的乘积为正，只要整个集合的元素中的负数的个数为偶数，那整个集合的元素乘积为正。

所以可以让这个集合有两种情况：

1. 所有元素为正

2. 所有元素中有偶数个负数

* 第三个集合：

只要整个集合中有一个零，那么无论其他元素为正数还是负数，最后集合元素乘积一定为零。

## 解法正确性分析：

* 第一个集合只有一个负数，所以乘积一定为负。

* 第二个集合的两种情况：

1. 所有元素均为正数，则乘积一定为正；

2. 所有元素中有偶数个负数， 其余为正数，则乘积一定为正。

* 第三个集合中有一个零，则乘积一定为零。

## 代码实现：

```
#include <iostream>
#include <cstdio>
#include <queue>
#define F1(i, a, b) for (int i = a; i <= b; ++i)
#define F2(i, a, b) for (int i = a; i >= b; --i)
using namespace std;

int a[101]; // a 数组存数列。
int n;
vector<int> S[4]; // 用 vector 存集合。

int main() {
	int fu = 0, sum = 0;
	scanf("%d", &n);
	F1(i, 1, n) {
		scanf("%d", &a[i]);
		if (a[i] < 0) ++sum; // 计数数列中负数的个数。
	}
	F1(i, 1, n) {
		if (a[i] < 0 && fu == 0) { // 如果数是第一个负数，
			fu = 1;
			S[1].push_back(a[i]); // 将此数放入第一个集合里。
			--sum;
		}
		else if (a[i] > 0 || (a[i] < 0 && sum % 2 == 0)) S[2].push_back(a[i]); // 如果数为正数或者剩余的负数个数为偶数，就把此数放入第二个集合里。
		else if (a[i] < 0 && sum % 2 == 1) {
			S[3].push_back(a[i]); // 如果剩余的负数个数为奇数，就把一个负数放入第三个集合里，这样就满足第二个条件。
			--sum;
		}
		else S[3].push_back(a[i]); // 0 放进第三个集合里。
	}
	F1(i, 1, 3) { // 输出
		printf("%d ", S[i].size());
		F1(j, 0, S[i].size() - 1)
			printf("%d ", S[i][j]);
		printf("\n");
	}
	return 0; // 好习惯
}
```

---

## 作者：离散小波变换° (赞：0)

## 题目大意

$n$ 个数，要求分成三个集合 $A,B,C$，使得：

$$\prod _ {x\in A} x<0,\prod _ {x\in B} x >0 ,\prod _ {x\in C} x =0$$

**保证有解**。

## 题解

这里提供一个代码非常简单的解法吧。

- 观察集合 $A$，我们发现，只需要塞一个负数就行了。
- 观察集合 $B$，我们发现，我们需要塞一个正数**或者两个负数**。
- 集合 $C$ 有一个好处：**任何多出来的数，都可以塞到** $\bm C$ **里面去**。

题目保证有解。那么，倘若我们给这些数排个序，最小的数**必定是负数**，于是可以直接扔到 $A$ 里面去；如果最大的数是正数，就可以直接扔到 $B$ 里面去，否则选择第二小的数和第三小的数，因为题目保证有解，说明**此时至少有两个负数**。剩下的全部丢到 $C$ 里面，因为剩下的数肯定有 $0$。同样，是因为题目有解。

于是，我们就能根据**保证有解**这个条件，得出一个非常简短的代码。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l;i<=r;i++)
#define dn(l,r,i) for(int i=l;i>=r;i--)
using namespace std;
const int MAXN =100+3;
int n,A[MAXN];
int main(){
    scanf("%d",&n); up(1,n,i) scanf("%d",&A[i]);
    sort(A+1,A+1+n),printf("1 %d\n",A[1]);
    if(A[n]<=0){
        printf("2 %d %d\n%d",A[2],A[3],n-3);
        up(4,n,i) printf(" %d",A[i]);
    } else{
        printf("1 %d\n%d",A[n],n-2);
        up(2,n-1,i) printf(" %d",A[i]);
    }
    puts("");
    return 0;
}
```

---

## 作者：☆木辛土申☆ (赞：0)

首先分析题目，因为一定有解，所以一定是有负数的，因为光凭正数和0是生不出负数的。

于是我们建立三个集合，正数集，负数集和0，在将所有数字分类好后，进行如下判断：

* 1.判断正数集中是否有元素，若没有，从负数集中选择两个元素放进正数集中，负负得正
* 2.判断负数集的元素个数是否为奇数个，若不是，从负数集中选择一个元素放入0的集合中

通过这两个判断，最多进行3次操作就能得到可行解

看了下其他题解，不知为什么他们把其他无用元素都插入0的集合中了，这样很浪费时间和空间的QwQ，0那么可爱，为什么要插那么多次（大雾

下面是代码：
```cpp
#include<cstdio>
#include<iostream>
#include<vector>

std::vector<int> a[3];

int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int temp;scanf("%d",&temp);
		if(temp<0) a[0].push_back(temp);
		else if(temp>0) a[1].push_back(temp);
		else a[2].push_back(temp);
	}
	if(!a[1].size()){
		for(int i=1;i<=2;i++){
			int x=a[0].back();
			a[0].pop_back();
			a[1].push_back(x);
		}
	}//判断1
	if(!(a[0].size()&1)){
		int x=a[0].back();
		a[0].pop_back();
		a[2].push_back(x);
	}//判断2
	for(int i=0;i<=2;i++){
		printf("%llu",a[i].size());
		for(auto j:a[i]) printf(" %d",j);puts("");
	}
	return 0;
}
```

---

