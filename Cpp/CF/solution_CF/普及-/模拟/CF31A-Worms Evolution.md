# Worms Evolution

## 题目描述

Vasechkin教授正在研究蠕虫的进化。最近他提出一种假说——所有蠕虫都是通过分裂而来。这里有n种形态不同的蠕虫。这些蠕虫有以下长度$a_1,a_2,\ldots,a_n$

为了证明他的理论，教授需要找到3种形态不同的蠕虫，其中第一个的长度是另外两个的和。帮助他完成这个吧。

## 样例 #1

### 输入

```
5
1 2 3 5 7
```

### 输出

```
3 2 1
```

## 样例 #2

### 输入

```
5
1 8 1 5 1
```

### 输出

```
-1
```

# 题解

## 作者：Eason_AC (赞：3)

## Content
有一个长度为 $n$ 的数组 $a_1,a_2,a_3,...,a_n$，试找出一个三元组 $(i,j,k)$，使得 $a_i=a_j+a_k$。

**数据范围：$3\leqslant n\leqslant 100,1\leqslant a_i\leqslant 1000,1\leqslant i,j,k\leqslant n,j\neq k$。**
## Solution
由于数据范围很小，因此我们可以直接 $\mathcal{O}(n^3)$ 枚举，每次枚举判断是否有一个数等于另外两个数的和就好了（注意，不能一个数同时取两次）。全枚举完了还没有找到，直接输出 $-1$。
## Code
```cpp
int n, a[107];

int main() {
	getint(n);
	_for(i, 1, n)	getint(a[i]);
	_for(k, 1, n)
		_for(i, 1, n)
			_for(j, 1, n)
				if(a[i] + a[j] == a[k] && i != j) {
					printf("%d %d %d", k, i, j);
					return 0;
				}
	printf("-1");
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

### 前言

越来越菜了，这种题目也要调半天。

### 分析

这道题目一看数据：

$3 \le n \le 100$ 

咦？那直接 $O(n^3)$ 暴力枚举 $3$ 个数呀 。

然后呢，这里的输出顺序应该是 $i,j,k$ 或者 $i,k,j$ 两个都可以，(反正 CF 有 SPJ 呀！

然后判一下，$i \ne j $ 并且 $j \ne k$ 并且 $k \ne i$ 这样子判一下，防止有重复的出来！

还有，$3$ 个循环分别要从 $1$开始，否则会有被很玄学的数据卡掉。(

然后就没什么要特别注意的了。

### 代码

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=105;
int n,a[INF];//定义变量头文件以及命名空间。
signed main()
{
        scanf("%d",&n);
        for (int i=1; i<=n; i++) {
                scanf("%d",&a[i]);
        }
        //读入数据。
        for (int i=1; i<=n; i++)
                for (int j=1; j<=n; j++)
                        for (int k=1; k<=n; k++) {//从 1 开始！
                                if (i==j || i==k || k==i) continue; //判断一下是否有重复的。
                                if (!((a[i]+a[j])^a[k])) {//这里我用的是位运算 异或，这样子可以加快速度，假如有一个数和它相同的数异或，就会变成 0 。
                                        printf("%d %d %d\n",k,j,i);//这里我用的是 k,j,i 的顺序。
                                        return 0;//找到了那么就跳掉。
                                }
                        }
        printf("-1\n");//否则就找不到了，就输出 -1。
        return 0;
}
```

### 写在后面的话

我这篇题解如果有错误，请您指出来，我将非常感谢！

**谢谢观赏！**

---

## 作者：ChthollyMeow (赞：1)

一眼看过去，$3\le n\le100$ ，直接 $O(n^3)$ 暴力枚举即可。

一个小细节：如果 $a_i=a_j+a_k$，那么只有 $i\ne j\ne k$ 的时候才能输出。

具体见注释。

```cpp
#include<cstdio>
using namespace std;
int main(){
    int n,a[105];
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                if(i==j||j==k||k==i){           //如果i,j,k中有两个相等
                    continue;                   //就跳过
                }
                if(a[i]==a[j]+a[k]){            //如果两两不等且满足条件
                    printf("%d %d %d\n",i,j,k); //输出
                    return 0;                   //直接退出，因为输出一组解即可。
                }
            }
        }
    }
    printf("-1\n");     //如果执行到这里了，那么说明不存在这样的三元组，输出-1。
    return 0;
}
```

------------

此时，我们顺利 A 过了这道题。

不过，爱优化&卡常的我们怎么会止步于此呢？

于是想到了一个简单的优化方法：

如果 $a_i=a_j+a_k$，而题目中说了数组是非负的，那么一定有 $a_i>a_j,a_i>a_k$。

所以考虑将原数组降序排列后从大到小枚举。

由于题目中说了 $1\le a_i\le1000$，值域很小，排序那部分可以直接计数排序 $O(n)$ 完事。

不过后面的枚举，仍然是 $O\left(\dfrac{n(n+1)(n-1)}{6}\right)$ 的~~请读者自证~~，简化后仍然是 $O(n^3)$，虽然卡掉了一部分常数，但多了个排序，仍然不够快。

继续优化。

至于代码，就不放了，毕竟这方法也是非常简单的。

------------

题目要求的，其实就是满足 $a_i=a_j+a_k$ 的三元组 $(i,j,k)$。

看到这道题之后，同学们难道没有想到一道有趣的题目么？

没错，就是这道：[P1102 A-B 数对](https://www.luogu.com.cn/problem/P1102)

那道题让求所有 $A-B=C$ 的数对，和这道题差不多啦。

唯一的区别是，这道题没有给出具体的 $C$。

不给出 $C$ 会导致什么后果呢？

想一想那道题是怎么做的吧：把 $A-B=C$ 改成 $A-C=B$，用一个 `map` 记录下所有的 $A-C$ 出现的值。

类似地，暴力记录所有 $a_i-a_j$ 的值即可。

（空间可能会炸）

------------

再优化的话......可以使用桶排序的思路，建桶。

不过空间复杂度大概率爆炸......（当然此题数据太水，我也不知道会不会炸）

可以考虑 Hash 算法。

举个例子：记录四个数 `1,4,7,114514`

那么如果建桶，我们就必须开一个大小为 $114514$ 的数组，但中间有 $114510$ 个地方都是空的。。。

所以，记录它们除以四的余数即可。

```
1%4=1,4%4=0,7%4=3,114514%4=2
```

所以只需要建一个大小为 $4$ 的桶即可。

[Hash 模板题](https://www.luogu.com.cn/problem/P3370)（这道题是字符串哈希，不过一样的啦QwQ）

使用这种思路，就能极大降低空间复杂度了。

------------

继续优化

然鹅我这个蒟蒻想不到继续优化的方法了![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)![/kk](https://cdn.luogu.com.cn/upload/pic/62227.png)

有没有大佬想到了继续优化的好办法呀？欢迎在评论区提出哦QwQ![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)![/kel](https://cdn.luogu.com.cn/upload/pic/62226.png)

---

## 作者：至成天下 (赞：1)

这道题由于数据只有3<=n<=100,所以只要暴力找出那三个数就行

直接三重循环，判断下标是否重复即可

上代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i)cin>>a[i];//读入
	for(int i=1;i<=n;++i){//暴力循环
		for(int j=1;j<=n;++j){
			for(int k=1;k<=n;++k){
				if(i==j||j==k||i==k)continue;//判断是否重复
				if(a[i]==a[j]+a[k]){//判断是否找到
					cout<<i<<' '<<j<<' '<<k<<endl;//输出
					return 0;
				}
			}
		}
	}
	cout<<-1<<endl;//找不到输出-1
	return 0;
}


```
然后你会发现第一个数据不对

没事那只是顺序有误，交上去会AC的


---

## 作者：Colead (赞：0)

# CF31A
### 1、前言
这道题我居然一次就AC了，这道黄题看似很难，但实际上可以很容易地AC。下面就详细阐述一下这道题的做法。
### 2、题意分析
这个（~~奇奇怪怪的~~）博士设想一种虫子长度是k厘米，而这种虫子是分裂繁殖的，可以分裂成两只长度和为k厘米的虫子。给你博士的虫子，问能不能验证他的猜想（也就是这些虫子里有没有两条虫子的长度之和等于另外一条虫子）。

翻译一下：就是给你一个数列，问你其中有没有两个数的和为第三个数。（清爽多了）
### 3、算法分析
我已经都看过了题解区各位神犇的代码，都是使用暴力枚举来做的（谁让n小于等于100呢？）。

不过我想了想，还是想为大家提供了一种时间复杂度快一点的做法（小于O（n^3))。

就不暴力枚举了。先把所有数据输入。然后**排序**（从而减小时间复杂度），最后枚举。

关键就在于排序啊！！！

排序完了以后数据顺序就乱啦！怎么办？

用结构体先把编号存下来就行啦！
### 4、代码出场

先把关键的结构体定义单独拎出来说一说：
```
struct wormdefiner
	{
	   int length,number;//长度与序号。
	};
wormdefiner worm[105];//数组。
int cmp(wormdefiner a,wormdefiner b)
{
	return a.length<b.length;//等一会儿sort的时候用。
}
```

再上完整代码：
```
#include <bits/stdc++.h>
using namespace std;
struct wormdefiner
	{
	   int length,number;	
	};
wormdefiner worm[105];
int cmp(wormdefiner a,wormdefiner b)
{
	return a.length<b.length;
}
int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>worm[i].length;//长度需要输入。
		worm[i].number=i;//编号直接赋值。
	}
	sort(worm+1,worm+n+1,cmp);//cmp的用场：以length为关键字比较。
	for(int i=n;i>=1;i--)//三重循环核心之一：从大到小
	{
		for(int j=i;j>=1;j--)
		{
			for(int k=1;k<=j;k++)//三重循环核心之二：逆向枚举
			{
				if(worm[i].length==worm[j].length+worm[k].length&&worm[j].number!=worm[k].number)//长度之和=长度，以及不能是同一只虫用两次。
				{
					cout<<worm[i].number<<" "<<worm[j].number<<" "<<worm[k].number<<endl;
					return 0;//结束。
				}
			}
		}
	}
	cout<<"-1"<<endl;//还没找到？实验失败。
	return 0;//好习惯。
}
```

### 5、尾声
这道题是一道适合（~~像我这样的~~）蒟蒻练手的题目，祝大家早日AC！！！

我是WT20071112。有问题珂以在评论区留言或私信我哦。

码字不易，还希望您可以动一动鼠标点个赞哦！

再见啦~

---

## 作者：LRL65 (赞：0)

记得有一句话：

**暴力出奇迹，打表出省一。**

所以暴力是最基础的，~~也是最玄学的~~。



------------
**我们拿道题一定要先看数据范围。**

这题的范围是：1<n<100。嗯？100以内？再看一眼题目，明显暴力呀。

那么来看看怎么暴力：

很简单呀，直接三重循环枚举下标，然后满足 $a_i+a_j=a_k$ 时就输出并且结束，最后如果还没有输出，说明没有，那么输出-1。

这里需要注意一个细节：

输出3个**不同**的整数 $i,j,k$ 

对，这里得是不同的，千万不要忘记。

上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105];
int main() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) {
			for(int k=1;k<=n;k++) {
				if(i==j||j==k||i==k)continue;//不要忘记是不同的
				if(a[i]==a[j]+a[k]) {
                    cout<<i<<" "<<j<<" "<<k<<endl;//直接输出并结束
                    return 0;
                }
			}
		}
	}
	cout<<-1<<endl;//没有就输出-1
	return 0;
}
```

---

