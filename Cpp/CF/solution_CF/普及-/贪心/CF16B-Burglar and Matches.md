# Burglar and Matches

## 题目描述

一个窃贼到火柴仓库偷火柴,仓库有 $m$ 个容器,第 $i$ 个容器有 $a_i$ 个火柴盒,其中每个火柴盒中有 $b_i$ 根火柴,窃贼最多可以拿 $n$ 个火柴盒 。

## 说明/提示

#### 数据规模与约定

$ 1 \le n \le 2 \times 10^8$，$1 \le m \le 20$，$1 \le a_i \le 10^8$，$1 \le b_i \le 10$ 。

## 样例 #1

### 输入

```
7 3
5 10
2 5
3 6
```

### 输出

```
62
```

## 样例 #2

### 输入

```
3 3
1 3
2 2
3 1
```

### 输出

```
7
```

# 题解

## 作者：StupidSeven (赞：3)

第一次写题解，希望管理员小哥哥给过QAQ

看到题目，嗯，这不是一道~~贪心~~（模拟）吗，还是那句话，大胆猜想，~~小心~~暴力求证

看题，基本思路：结构体+排序，每种火柴盒里火柴的数量按大到小排好序，一个一个加，只要加的次数=n，程序结束

这里要讲一个东西：结构体排序

# sort大法好啊！
我们知道sort函数可以将数组里的东西按按小到大排序（如果是char类型或者是string类型的即按字典序排序）可是呢，单单一个sort函数，并不能够达到让我们控制排序的顺序，这时就要自己编写一个cmp函数。

比如要让5个int类型的数，按大到小排序，我们可以写一个cmp函数：
```
bool cmp(int a,int b){
	return a>b;
}
int a[5]={23,32,1,39,40};
……
sort(a,a+5,cmp);
```
输出：40 39 32 23 1

再比如按大到小排序字符串，将参数的类型改为string即可。

接着，如果有一个结构体如下：
```
struct node{
	int x,y;
}a[5];
```
我们要通过y的值将每个结构体从小打到排序，也就是y的值越小，序号越靠前，cmp函数如下：
```
bool cmp(node a,node b){
	return a.y<b.y;
}
```
即可将结构体排序。

本题代码如下：
```
#include<iostream>
using namespace std;
struct node{
    int x,y;//分别表示第i种的火柴盒数和火柴数
}a[21];//结构体声明
bool cmp(node a,node b){return a.y>b.y;}//cmp函数
int n,m,s,t;//n，m如题，s储存当前累加的火柴数量，t表示当前累加的火柴盒数量
signed main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>a[i].x>>a[i].y;//按题意输入
	sort(a+1,a+1+m,cmp);//快排
        for(int i=1;i<=m;i++){
    	    for(int j=1;j<=a[i].x;j++){
    		t++;//当前增加火柴盒数
    		s+=a[i].y;//因为这个已经是当前火柴数最大的一种，直接累加
    		if(t==n) break;//如果当前的火柴盒数=n，跳出循环
    	    }
    	if(t==n) break;//再次跳出，毕竟刚才只跳出了一个循环
        }
        cout<<s;//输出答案
	return 0;//要有好习惯哟
}
```
本人的第一篇题解就到这啦，如果别的大佬有一些别的什么建议或意见的话可以私信我哦QWQ

---

## 作者：灵光一闪 (赞：1)

emming……，这题好像是贪心（反正用的是这个思想就对了

code：（实在想不出来讲什么了……）
```
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<cstdio>

#include<map>
#include<vector>
using namespace std;
pair <int,int> p[23];
long long ans=0;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin>>p[i].second;//这里要先输后面
        cin>>p[i].first;//因为sort排序是先排前面，如果有相同的再排后面
    }
    sort(p,p+m);
    for(int i=m-1;i>=0;i--){
        if(p[i].second<=n){//能把这个全拿走
            ans+=p[i].first*p[i].second;
            n-=p[i].second;
        }
        else{//不能
            ans+=p[i].first*n;
            n=0;
            break;
        }
        if(n==0){//不能再多拿一点东西了
            break;//跳出循环
        }
    }
    cout<<ans<<endl;
    return 0;
}
```
The End.

---

## 作者：Allanljx (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF16B)
[CF传送门](https://codeforces.com/problemset/problem/16/B)
## 题意
有 $m$ 种数，，第 $i$ 种数是 $b[i]$ 有 $a[i]$ 个，最多能取 $n$ 个数，求能取到的最大值。
## 思路
用结构体存数，对数的大小排序，再用贪心去取最大值。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
    int x,y; 
}a[21];
bool cmp(node a,node b)//结构体排序 
{
	return a.y>b.y;
}
int main()
{
	long long n,m,sum=0;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		cin>>a[i].x>>a[i].y;
	}
	sort(a+1,a+m+1,cmp);//排序 
	for(int i=1;i<=m;i++)
	{
		if(n>a[i].x)//如果还可以取 
		{
			n=n-a[i].x; 
			sum+=a[i].y*a[i].x;
		}
		else //否则去取尽量大的数 
		{
			sum+=a[i].y*n;
			cout<<sum<<endl;
			return 0;
		}
	}
	cout<<sum<<endl;//如果没有取完n个数 
	return 0;
}
```


---

## 作者：Integerss (赞：0)

# 算法
显而易见的贪心，按照正常人的思路肯定是一直取根数多的火柴盒。

# 代码
想怎么搞就怎么搞。

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct fire{
	int a,b;
}f[30];
bool cmp(fire x,fire y){
	return x.b>y.b;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>f[i].a>>f[i].b;
	}
	sort(f+1,f+1+m,cmp);//贪心 
	int cnt=0,sum=0;//赋初值 
	//下面是暴力的做法 
	for(int i=1;i<=m;i++){//枚举每个容器 
		for(int j=1;j<=f[i].a;j++){//枚举每个火柴盒 
			cnt++;
			sum+=f[i].b;
			if(cnt==n){
				break;
			}
		}
		if(cnt==n){
			break;
		}
	}
	cout<<sum<<endl;
	return 0;
}
```


---

## 作者：jiang_cheng (赞：0)

## 解题思路：
贪心！！！用结构体排序， 然后一直贪火柴数大的火柴盒，注意！小偷最多能偷的火柴盒可能大于有的。
## 附上代码：
```cpp
#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 21;

int n, m, ans;
struct E{
  int a, b;
} e[kMaxN];

bool C(E e1, E e2) {
  return e1.b > e2.b;
} //定义结构体排序

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].a >> e[i].b;
  }
  sort (e + 1, e + m + 1, C);
  for (int j = 1; j <= m;) {
    if (n >= e[j].a) {
      ans += e[j].a * e[j].b;
      n -= e[j].a;
      j++;
    } else {
      ans += n * e[j].b;
      cout << ans;
      return 0;
    }
  }
  cout << ans;
  return 0;
}


```


---

## 作者：happybob (赞：0)

这道题目是最简单的贪心问题啦！用STL的二元结构体pair或者用struct，class都可以解决的！

那么我用的是pair，比struct似乎是慢了一点，1.27s,自定义排序 + sort

```cpp
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

#define p pair<int, int>//宏定义一下，不然写得多

int n, m, x, y;

bool cmp(p a, p b)//自定义排序
{
    return a.second > b.second;//不管first，只排second
}

p a[25];

int main()
{
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
    {
        cin >> x >> y;
        a[i] = make_pair(x, y);//读入可以用make_pair，也可以用直接first和second，都行的哦！
    }
    sort(a + 1, a + m + 1, cmp);//排序
    int ans = 0, s = 0;//s是现在的火柴盒数量，ans是答案
    for(int i = 1; i <= m; i++)
    {
        s += a[i].first;//加上火柴盒的数量
        if(s > n)//如果已经多于可以取的就加上现在还能取的
        {
            ans += (n - s + a[i].first) * a[i].second;
            break;//循环停下来
        }
        ans += a[i].first * a[i].second;//直接乘

    }
    cout << ans << endl;
    return 0;
}
```

End.

哦，还没end，求过

End.

哦，还要求赞

End.

---

## 作者：Fat_Fish (赞：0)

本题运用**贪心**思想，一直取根数多的火柴盒，直到不能取为止。涉及：手写cmp，sort排序，结构体，时间复杂度$O(nlogn)$

$code$
------------

```cpp
#include<iostream>
#include<bits/stdc++.h>//万能头
using namespace std;

struct Node{
	
	int Hs,Gs;//火柴盒数，火柴根数
};

bool cmp(Node x,Node y){
	
	return x.Gs>y.Gs;//手写cmp，按每盒根数从大到小排
}

int main(){
	int n,m;
	cin>>n>>m;
	Node a[m+1];//m个容器
	
	for(int i=1;i<=m;++i){
		
		cin>>a[i].Hs>>a[i].Gs;//循环输入
	}
	
	sort(a+1,a+1+m,cmp);//sort排序，STL库内
	
	int flag=0,sum=0;//flag是已偷盒数，sum为火柴根数（答案）
	
	for(int i=1;i<=m;++i){//循环
		
		for(int j=1;j<=a[i].Hs;++j){//一盒一盒地加
			
			if(flag==n){
				break;//若已偷n盒，结束
			}
			sum+=a[i].Gs;//累加根数
			++flag;//累加盒数
		}
	}
	cout<<sum;//输出
	return 0;
}
```


---

## 作者：hensier (赞：0)

这道题可以采用$struct+STL:sort$。

其实这道题有一点背包的性质，但是比$0-1$，完全背包要简单得多。只需要$sort$价值即可。价值大的当然先取，价值小的放在后面。


```cpp
#include<bits/stdc++.h>//万能头文件
#define f(x)for(int i=0;i<x;i++)//宏定义(0,x)for循环
#define min(a,b)a<b?a:b//宏定义min
int n,m,i,s,a;
struct box
{
    int x,y;
}b[20];//定义struct
bool cmp(box A,box B)//compare函数
{
    return A.y>B.y;
}
int main()
{
    scanf("%d%d",&n,&m);
    f(m)scanf("%d%d",&b[i].x,&b[i].y);
    std::sort(b,b+m,cmp);
    f(m)
    {
        a=min(b[i].x,n);//取剩余背包容量和当前重量的最小值
        n-=a;//减掉
        s+=a*b[i].y;//价值累加
        if(!n)break;//背包容量=0就退出
    }
    printf("%d",s);
}
```

---

## 作者：zhq_2018 (赞：0)

这一题其实是一个结构体+贪心。我们需要定义一个结构体变量，然后来存储火柴盒的数量a和每盒里的火柴数量b。

------------
主要思路就是：将数组进行排序，优先选择每盒火柴数量大的。如果拿的盒子的数量没超过，就将答案更新。如果超过了，再进行调整。话不多说，上代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
struct node{
	int a,b,c;
}a[25];
bool cmp(node c,node d)
{
	return c.b > d.b;
}
int ans,k;//k为目前拿的火柴盒数量
int main()
{
	cin >> n >> m;//输入n和m
	for(int i = 1;i <= m;i++)
	{
		cin >> a[i].a >> a[i].b;
		a[i].c = a[i].a * a[i].b;//算出每个容器内火柴的总个数
	}
	sort(a + 1,a + m + 1,cmp);//进行排序
	for(int i = 1;i <= m;i++)
	{
		ans += a[i].c;//如果拿的火柴盒数量不超过n，那么就将答案加上当前容器内火柴的总个数
		k += a[i].a;
		if(k > n)//如果超过了
		{
			ans -= (k - n) * a[i].b;//那么就减去超过部分的火柴数量
			break;
		}
	}
	cout << ans << endl;//输出结果
	return 0;//华丽的结尾
}

```
谢谢观看

---

