# Search for Pretty Integers

## 题目描述

You are given two lists of non-zero digits.

Let's call an integer pretty if its (base $ 10 $ ) representation has at least one digit from the first list and at least one digit from the second list. What is the smallest positive pretty integer?

## 说明/提示

In the first example $ 25 $ , $ 46 $ , $ 24567 $ are pretty, as well as many other integers. The smallest among them is $ 25 $ . $ 42 $ and $ 24 $ are not pretty because they don't have digits from the second list.

In the second example all integers that have at least one digit different from $ 9 $ are pretty. It's obvious that the smallest among them is $ 1 $ , because it's the smallest positive integer.

## 样例 #1

### 输入

```
2 3
4 2
5 7 6
```

### 输出

```
25
```

## 样例 #2

### 输入

```
8 8
1 2 3 4 5 6 7 8
8 7 6 5 4 3 2 1
```

### 输出

```
1
```

# 题解

## 作者：引领天下 (赞：5)

来一发不一样的思路

你们都排序，可是我

# 不排序！

## 其实，对于这种判断一个数字有没有在两个数组里出现的题目用桶最方便

具体做法：

先读入两个数组，在桶中标记；

然后从1扫到9，有同时出现的就输出

不然找最小的

上巨短代码

```cpp
#include <cstdio>
int a[10],b[10],n,m,x,y;
int main(void){
    scanf ("%d%d",&n,&m);
    for (int i=0;i<n;i++)scanf ("%d",&x),a[x]=1;
    for (int i=0;i<m;i++)scanf ("%d",&x),b[x]=1;
    for (int i=1;i<10;i++)if (a[i]&&b[i])return !printf ("%d",i);
    for (int i=1;i<10;i++)if (a[i]){x=i;break;}
    for (int i=1;i<10;i++)if (b[i]){y=i;break;}
    if (x<y)printf ("%d",x*10+y);
    else printf ("%d",y*10+x);
}
```

---

## 作者：Neoomgg (赞：1)

# 来，让我们欢快的使用集合！

详见代码，一个并集解决一切·=·

```python
n, m = map(int, input().split())
a = set(map(int, input().split()))
b = set(map(int, input().split()))
c = min(a)
d = min(b)
e = a & b
if len(e) != 0:
    print(min(e))
else:
    print(str(min(c, d)) + str(max(c, d)))

```

---

## 作者：B_lhx (赞：0)

[CF870A Search for Pretty Integers](https://www.luogu.com.cn/problem/CF870A)
===
芝士：排序

思路：排序，如果重复，输出，否则输出首位连接
```
#include<bits/stdc++.h>
using namespace std;
int main(){
int n,m;//n和m
cin>>n>>m;//输入
int a[10005],b[100005];//定义数组安ab
for(int i = 0;i<n;i++){//循环输入a
	cin>>a[i];//输入
}
for(int i = 0;i<m;i++){//循环输入b
	cin>>b[i];//输入
}
sort(a,a+n);//a排序
sort(b,b+m);//b排序
for(int i = 0;i<n;i++){//循环a
	for(int j = 0;j<m;j++){//循环b
		if(a[i]==b[j]){//如果有重复
			cout<<a[i];//输出
			return 0;//结束-不管一位数再大也比两位数小
		}
	}
}
cout<<min(a[0],b[0])<<max(a[0],b[0]);//输出两个数组开头
return 0;
}
```


---

## 作者：OdtreePrince (赞：0)

# -模拟-

如果找到两个数组共同拥有的数，直接输出。

否则找出两个数组中最小的两个数，输出组合起来的数的最小值

完美AC，相信蒟蒻日后总有一天能蜕变！

~~~
#include<bits/stdc++.h>
using namespace std;
int n,m,a,b1[10],b=1,c=1,b2[10],k1,k2;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&a);
        while(a>0){
            b1[a%10]++;
            a/=10;
        }
    }
    for(int i=1;i<=m;i++){
        scanf("%d",&a);
        while(a>0){
            b2[a%10]++;
            a/=10;
        }
    }
    for(int i=0;i<10;i++){
        if(b1[i]&&b2[i]){
            cout<<i;
            return 0;
        }
    }
    for(int i=0;i<10;i++){
        if(b1[i]&&b) k1=i,b=0;
        if(b2[i]&&c) k2=i,c=0;
    }
    if(k1>k2) cout<<k2<<k1;
    else cout<<k1<<k2;
    return 0;
}
~~~

---

## 作者：PC_DOS (赞：0)

直接模拟即可。

首先将两个数组升序排序，判断一下有没有公共的项目，如果有就输出最小的那一项(由于数组已排序，第一个找到的肯定最小)。如果没有就比较两个数组的第一项(即最小项)，并将这两个数升序输出(保证十位数尽量小)即可。

代码:
```
#include <iostream>
#include <algorithm>
using namespace std; //头文件和命名空间
int main(){
	ios::sync_with_stdio(false); //提高输入输出速度
	int nCount1, nCount2, iMin1, iMin2, arrNums1[9], arrNums2[9],i,j; //nCount1、nCount2-两个数组的项数，iMin1、iMin2-两个数组中的最小项，arrNums1、arrNums2-两个数组，i，j-循环计数器
	cin >> nCount1 >> nCount2; //读入项数
	for (i = 0; i <= nCount1 - 1; ++i){ //读入第一个数组
		cin >> arrNums1[i];
	}
	for (i = 0; i <= nCount2 - 1; ++i){ //读入第二个数组
		cin >> arrNums2[i];
	}
	sort(arrNums1, arrNums1 + nCount1);
	sort(arrNums2, arrNums2 + nCount2); //将两个数组升序排序
	for (i = 0; i <= nCount1 - 1; ++i){ //找一下有没有公共的项目
		for (j = 0; j <= nCount2 - 1; ++j){
			if (arrNums1[i] == arrNums2[j]){ //如果找到(由于数组已排序，第一个找到的肯定最小)
				cout << arrNums1[i]; //输出
				goto endapp; //结束
			}
		}
	}
	iMin1 = arrNums1[0];
	iMin2 = arrNums2[0]; //保存两个数组的最小项
	if (iMin1 > iMin2) //比较两个数组的第一项(即最小项)
		cout << iMin2 << iMin1; //将这两个数升序输出(保证十位数尽量小)
	else
		cout << iMin1 << iMin2; //将这两个数升序输出(保证十位数尽量小)
endapp:
	return 0; //结束
}
```

---

## 作者：花千树 (赞：0)

**本题还是~~很水的~~**

**考察知识点：排序 模拟 ~~语文~~**

~~（语文不好题目都看不懂）~~

## 然鹅

**审题需要仔细！仔细！仔细！（重要事情说三遍）**

**最小的数，你们的数学老师没有告诉你们~~一位数比二位数小吗~~**

**看到身边一群朋友排完序就判断第一个相不相同，然后输出最小的二位数，结果悲惨的爆零…………**
# Duang
**本题思考正确姿势！**~~（躺着）~~

1、读完排序（不用说的，sort）

2、N*M扫一遍（数据水，想剪枝也可以），如果有相同的（一位数），输出，return 0;

3、如果没有快乐的return 0;说明不是一位数，直接输出a数组和b数组中，小的数*10+大的数，愉快输出。

代码不写注释了~~（其实是因为本人懒，其实讲的这么清楚，思路分析的如此明确，都不想贴代码了。。）~~
```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n,m,a[10],b[10];
int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)cin>>a[i];
	for(int i=0;i<m;i++)cin>>b[i];
	sort(a,a+n);
	sort(b,b+m);
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i]==b[j]){
				cout<<a[i]<<endl;
				return 0;
			}
		}
	}
	if(a[0]>b[0])cout<<b[0]*10+a[0]<<endl;
	else cout<<a[0]*10+b[0]<<endl;
	return 0;
}
```
#### ~~这应该是史上写得最详细的题解，~~管理员给过吧！



---

