# Laptops

## 题目描述

有一天Dima和Alex正在讨论关于 $n$ 台笔记本电脑的价格与质量。Dima认为价格高的笔记本质量也高，而Alex认为笔记本是物美价廉，价格低的笔记本质量反而高。

正当他们争（吵）论得不可开交之时，您过来了。现在您需要写出一个程序去确认谁是谁非。

## 样例 #1

### 输入

```
2
1 2
2 1
```

### 输出

```
Happy Alex
```

# 题解

## 作者：cbyybccbyybc (赞：7)

## CF中的水题！！！
~~不知道为何是橙题（普及-）~~                            
~~建议评为入门难度（我啥也没说）~~
### AC记录！！！
###  先看下这个标程——————————————————————————————————————
###  ——————————————begin——————————————————
```cpp
#include<bits/stdc++.h>//万能库
using namespace std;
struct note
{
    int zhiliang,qian;//定义结构体，分别有价格（qian）&质量（zhiliang）
}a[100000];//方便排序
bool tmp(note aa,note bb)
{
    if(aa.qian!=bb.qian)//先按价格排
    //其实按质量排也可以
    return aa.qian>bb.qian;
    else//如果一样，按质量排
    return aa.zhiliang>bb.zhiliang;
}
int main()
{
    int n;
    cin>>n;//输入个数
    for(int i=0;i<n;i++)
    cin>>a[i].qian>>a[i].zhiliang;//输入价格&质量
    sort(a,a+n,tmp);//快速排序
    for(int i=0;i<n;i++)
    {
        if(a[i].zhiliang<a[i+1].zhiliang)
        {
            cout<<"Happy Alex";//质量小于后一个，物美价廉，Alex开心！！！
            return 0;
        }
    }
    cout<<"Poor Alex";//没有一个物美价廉，Alex不开心  ￣へ￣ QAQ
    return 0;
}
```
### ————————————————————end——————————————————
## 感谢支持！！！
#### PS.本蒟蒻博客https://www.luogu.org/blog/3345039979cby/

---

## 作者：OdtreePrince (赞：5)

# -贪心-

本题不能暴力枚举，O(n^2)，保证爆掉。

因此，本题得用贪心思想，先按价格排序，从高到低；

其次，把1~i中质量最低的找出来，用minn数组表示

最后，从后往前找，保证前面的价格高，因此只需比较bj[i].b与minn[i]的大小，bj[i].b大的话，输出Happy Alex，退出；循环结束后，如果未退出，输出Poor Alex。

蒟蒻的蜕变，祝各位神犇暑假多刷题，成为神神犇！

~~~
#include<bits/stdc++.h>
using namespace std;
struct data{
    int a,b;
}bj[100005];
int n,minn[1000005];
bool cmp(const data x,const data y){
    return x.a>y.a;
}
int main(){
    minn[0]=2147483647;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&bj[i].a,&bj[i].b);
        minn[i]=min(minn[i-1],bj[i].b);
    }
    sort(bj+1,bj+n+1,cmp);
    for(int i=1;i<=n;i++){
        minn[i]=min(minn[i-1],bj[i].b);
    }
    for(int i=n;i>1;i--){
        if(bj[i].b>minn[i-1]){
            cout<<"Happy Alex";
            return 0;
        }
    }
    cout<<"Poor Alex";
    return 0;
}~~~

---

## 作者：ADivT (赞：5)

本题看到数据范围发现不能直接枚举$O(n^2)$的做法,会超时.

所以就要引入贪心算法,注意到Alex要求**物美价廉**,所以可以考虑按质量或价格排序(这里我是按质量排序),然后顺序查找即可,时间复杂度$O(nlogn)$,瓶颈在于排序,
代码如下:
```cpp
#include<bits/stdc++.h>

#define rep(i,o,p) for(register int i=o;i<=p;++i)

using namespace std;

int n,is_pr=0;

struct node{
	int value,weight;
}p[100010];

bool cmp(node a,node b){
	return a.weight==b.weight?a.value>b.value:a.weight>b.weight;
}

int main(){
	scanf("%d",&n);
	rep(i,1,n)scanf("%d%d",&p[i].value,&p[i].weight);
	sort(p+1,p+n+1,cmp);
	rep(i,1,n)if(p[i].value<p[i+1].value&&!is_pr)is_pr=printf("Happy Alex");
	if(!is_pr)printf("Poor Alex");
	return 0;
}
```
这题到这里就AC了.不留个赞再走吗

---

## 作者：ygl666666 (赞：5)

## 题意
n个笔记本，一个人觉得价格高质量高，另一个相反，问那个是对的。
## 思路
因为题目里说了，有价格低，质量高的就输出Happy Alex，所以判断有没有质量大于价格的，如果有就输出Happy Alex，否则就输出Poor Alex即可。
```
/**/
#include<bits/stdc++.h>
using namespace std;
int n,a,b; 
int main(){
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>a>>b;
		if(b<a){//如果价格小于质量
			cout<<"Happy Alex"<<endl;//alex就对了
			return 0;
		}
	}
	cout<<"Poor Alex"<<endl;
	return 0;
}

```
## End

---

## 作者：Kevin施黄凯 (赞：3)

Hello,本蒟蒻又来发题解了！

今天我们讲 CF456A 【Laptops】

作为CF难得一遇的水题

相信很多人都想试一试

看了各种大佬的代码

我的代码真是~

# 短

首先，我先把我的代码贴出来：

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n,a,a1,b,b1;
    cin>>n>>a<<a1<<b<<b1;
    if(a>a1&&b>b1)cout<<"Happy Alex";
    else cout<<"pool Alex";
}
```
没错，你没看错！

就是这么短！

[AC记录](https://www.luogu.com.cn/record/32215404)

下面我来讲一下这道题目

首先先定义变量，这个大家都会，我就不讲了。

其实这个程序里面最重要的就是if语句

题目上说了，**一台的价格比另一台低且质量比另一台高**

就是说当a>a1&&b>b1的时候输出Happy Alex，相反就是else cout<<"pool Alex"。

这道题其实就是考你的基本功，判断语句。

如果还有不会的，可以私信我。

既然看到这里了，就点个赞再走吧！


---

