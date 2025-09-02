# Toy Cars

## 题目描述

Little Susie, thanks to her older brother, likes to play with cars. Today she decided to set up a tournament between them. The process of a tournament is described in the next paragraph.

There are $ n $ toy cars. Each pair collides. The result of a collision can be one of the following: no car turned over, one car turned over, both cars turned over. A car is good if it turned over in no collision. The results of the collisions are determined by an $ n×n $ matrix $ А $ : there is a number on the intersection of the $ і $ -th row and $ j $ -th column that describes the result of the collision of the $ і $ -th and the $ j $ -th car:

- $ -1 $ : if this pair of cars never collided. $ -1 $ occurs only on the main diagonal of the matrix.
- $ 0 $ : if no car turned over during the collision.
- $ 1 $ : if only the $ i $ -th car turned over during the collision.
- $ 2 $ : if only the $ j $ -th car turned over during the collision.
- $ 3 $ : if both cars turned over during the collision.

Susie wants to find all the good cars. She quickly determined which cars are good. Can you cope with the task?

## 样例 #1

### 输入

```
3
-1 0 0
0 -1 1
0 2 -1
```

### 输出

```
2
1 3 ```

## 样例 #2

### 输入

```
4
-1 3 3 3
3 -1 3 3
3 3 -1 3
3 3 3 -1
```

### 输出

```
0
```

# 题解

## 作者：封禁用户 (赞：3)

**题目：**

[CF545A Toy Cars](https://www.luogu.com.cn/problem/CF545A)

------------
**题意：**

   一个二维数组中，有$-1$、$0$、$1$、$2$、$3$这五种数字，车有没有翻分以下三种情况：
   
   - 当为$1$时，记录第$i$辆车翻车；
   - 当为$2$时，记录第$j$辆车翻车；
   - 当为$3$时，记录第$i,j$辆车翻车；
   
   问：到最后一共有多少辆车没翻，并输出它们的编号
   
**解法：**

   定义一个数组记录每辆车的状态，边输入边判断边记录即可
   
**$Code:$**

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[105][105],ans;//ans记录翻车的数量
bool b[105];//b数组记录每辆车的状态（false表示车没翻，true表示车翻了）
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		cin>>a[i][j];
    		if(a[i][j]==1 && !b[i])b[i]=true,ans++;//将编号i的车标记为true
    		else if(a[i][j]==2 && !b[j])b[j]=true,ans++;//将编号j的车标记为true
    		else if(a[i][j]==3)//将编号i、j的车标记为true
	    		{
	    			if(!b[i])b[i]=true,ans++;
	    			if(!b[j])b[j]=true,ans++;
	    		}
    	}
    }
    cout<<n-ans<<endl;//用车总数减去翻车的数量
    if(n-ans!=0)//假如有车没翻
    {
    	for(int i=1;i<=n;i++)//如果为false，输出
    		if(!b[i])cout<<i<<" ";
    }
    return 0;
}
```


---

## 作者：sel_fish (赞：2)

[安利一波某个蒟蒻的博客](https://xcgzyangzhihao.blog.luogu.org/)

因为被拒绝了好多次，解释太少，所以我准备认真的写一下这道**水题**的题解
- 首先建一个二维f数组来存储n辆车的情况
- 如果相撞就赋值为1
- 由题意可知
1. 只有第i辆车在碰撞中翻车。
2. 只有第j辆车在碰撞中翻车。
3. 两辆车在碰撞过程中翻车。
- 所以可以直接这样存储
- 最后用循环判断就可以了 

```cpp
#include<bits/stdc++.h>//神奇万能头
using namespace std;
int ans;
int f[101];
int main()
{
	int n;
	cin>>n;
	int x;
	for(int i=1;i<=n;i++)
	{
	   for(int j=1;j<=n;j++)
	   {
		   scanf("%d",&x);
		   if(x==1) f[i]=1;
		   if(x==2) f[j]=1;
		   if(x==3)
		   {//都赋值为1
		       f[i]=1;
		       f[j]=1;
		   }
	   }
	}
	for(int i=1;i<=n;i++)
	{//仍然为0，表示没有翻
	    if(!f[i]) ans++;
	}
	cout<<ans<<endl;
	if(!ans) return 0;//没有车相撞
	for(int i=1;i<=n;i++)
	{
	    if(!f[i]) printf("%d ",i);
	}
	return 0;
//我可以防止抄袭哦
}

---

## 作者：LYR_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF545A)

[安利一下博客](https://www.cnblogs.com/Ryan-juruo/p/12825365.html)

[洛谷博客](https://ryan14722579.blog.luogu.org/solution-cf545a#)

~~太弱了，只能写写A题的题解~~
### 题意
给你一个 $n·n$ 的矩阵，翻车分三种情况：
- 如果 $a_i,_j=1$ ，记录第 $i$ 辆车
- 如果 $a_i,_j=2$ ，记录第 $j$ 辆车
- 如果 $a_i,_j=3$ ，记录第 $i$ 和 $j$ 辆车
问最后总共记录多少辆车（不重复）？它们分别是第几辆？

### 思路
这题可以用set ~~(好喜欢用set)~~，因为set可以去重，用在这里可以有效减少时间复杂度。
一边输入一边将 $i$ 或 $j$ 存入set并标记bool数组，然后输出 ```n-set的长度```，最后再输出没有被标记的下标。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=110;
int n;
bool f[N];
int main() {
    memset(f,false,sizeof f);
    cin>>n;
    set<int> s;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            int x;
            cin>>x;
            if(x==1) {
                s.insert(i);
                f[i]=1;
            }
            else if(x==2) {
                s.insert(j);
                f[j]=1;
            }
            else if(x==3) {
                s.insert(i);
                s.insert(j);
                f[i]=f[j]=1;
            }
        }
    }
    cout<<n-(int)s.size()<<endl;
    for(int i=1;i<=n;i++) if(!f[i]) cout<<i<<" ";
    return 0;
}
```

---

## 作者：hgoicjl (赞：0)

[CF545A题目](https://www.luogu.org/problemnew/show/CF545A)

[我的博客](https://www.luogu.org/blog/cmine/)
### 思路：
|  -1|  0| 0 |
| -----------: | -----------: | -----------: |
| 0 | -1 | 1 |
| 0 | 2 | -1 |
中的第二行第三列和第三行第二列其实是等价的，都表示了第二辆车被撞毁

我们只需要按行处理，判断该车是否被撞毁，并进行计数，最后输出即可

```
#include<bits/stdc++.h>
using namespace std;
//作者@hgoicjl
int mian()//防复制黏贴
{
	int a,b[105]/*记录所有没有翻车辆的编号*/,c,ans=0/*用来计没有翻的车的数量*/;
	cin>>a;
	for(int i=1;i<=a;i++)
	{
		int ok=0;
		for(int j=1;j<=a;j++)
		{
			cin>>c;
			if(c==1||c==3)//1，3都表示该辆车被撞毁
				ok++;
		 } 
		 if(ok==0)//对没有撞毁的车进行操作
		{
			ans++;//记录数量
			b[ans]=i;//记录编号
		}
	}
	cout<<ans<<endl;//输出数量
	for(int i=1;i<=ans;i++)
	{
		if(i==1)
			cout<<b[i];//按格式要求输出编号
		else
			cout<<' '<<b[i];
	}
	return 0;
}
```

---

