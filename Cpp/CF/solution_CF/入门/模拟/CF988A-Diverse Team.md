# Diverse Team

## 题目描述

给定n和k和n个元素的数列，请在这个数列中找k个不同的元素。
如果可行，则输出“YES”和其中一个答案（可能有多个答案）的元素编号。
否则输出“NO”。


感谢@南方不败 提供翻译

## 样例 #1

### 输入

```
5 3
15 13 15 15 12
```

### 输出

```
YES
1 2 5 
```

## 样例 #2

### 输入

```
5 4
15 13 15 15 12
```

### 输出

```
NO
```

## 样例 #3

### 输入

```
4 4
20 10 40 30
```

### 输出

```
YES
1 2 3 4 
```

# 题解

## 作者：OdtreePrince (赞：2)

# -模拟-

由于题目说了，输入的数小于100，因此用b数组来标记
1~100中的i是否出现，并标记它的序号。

统计不同的数的个数，如果小于k，输出NO；

否则，输出YES，换行，依次输出序号，直到k为0.

~~~
#include<bits/stdc++.h>
using namespace std;
int t,b[105],n,k,sum;
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        scanf("%d",&t);
        b[t]=i;
    }
    for(int i=1;i<=100;i++){
        if(b[i]) sum++;
    }
    if(sum>=k) cout<<"YES"<<endl;
    else{
        cout<<"NO";
        return 0;
    }
    for(int i=1;i<=100&&k;i++){
        if(b[i]){
            cout<<b[i]<<' ';
            k--;
        }
    }
    return 0;
}
~~~

---

## 作者：miaohongxuan (赞：0)

[原题链接](https://www.luogu.com.cn/problem/CF988A)

拿到这道题，我脑子里瞬间蹦出来一个思路：使用一个数组 $b$ ，下标为目标元素，内容为元素编号，再加一个变量 $sum$ 记录一共有几种不同的元素。先for循环读入，顺便判断是否存在，并记录在 $b$ 和 $sum$ 中。然后与 $k$ 做比较。最后for循环输出。

---

### 实现过程

**1.标准格式与变量、数组定义**

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std; 
int k,n,sum = 0,b[105] = {0},a[105];
int main(){
	
	return 0;
}
```

**2.输入**

```cpp
cin >> n >> k;
for(int i = 1; i <= n; i++){
	cin >> a[i];
}
```

**3.判断是否存在，并记录在 $b$ 和 $sum$ 中**

```cpp
if(b[a[i]] == 0){//判断是否存在
	b[a[i]] = i;//记录在b中：
//i 就是元素编号，a[i]就是第i次循环中输入的数
	sum ++;//不同的元素加一
}
```

**4.输出**

```cpp
	if(sum < k){//如果不足
		cout << "NO" ;//输出NO
		return 0;//跑路
	}
	cout << "YES" << endl;//因为NO已经跑路，直接输出
	for(int i = 1; i <= 105 && k/*如果已经达到数量，就可以停了*/; i++){
		if(b[i] == 0){//如果是空的
			continue;//跳过
		}
		cout << b[i] << " ";//因为已经跑路，直接输出
		k--;//还要的数量减1
	}
```

又切了一道红题！\\(^o^)/

### 完整无注释代码

**请勿抄袭**

```cpp
#include<bits/stdc++.h>//万能头文件 
using namespace std; 
int k,n,sum = 0,b[105] = {0},a[105];
int main(){
	cin >> n >> k;
	for(int i = 1; i <= n; i++){
		cin >> a[i];
		if(b[a[i]] == 0){
			b[a[i]] = i;
			sum ++;
		}
	}
	if(sum < k){
		cout << "NO" ;
		return 0;
	}
	cout << "YES" << endl;
	for(int i = 1; i <= 105 && k; i++){
		if(b[i] == 0){
			continue;
		}
		cout << b[i] << " ";
		k--;
	}
	return 0;
}
```


---

## 作者：_•́へ•́╬_ (赞：0)

## $map$~~真香~~
## 竟然没有人用~~这么香的~~$map$写，太神奇了
```cpp
#include<stdio.h>
#include<map>
#define rpt(n) for(register int ttxyc=0;ttxyc<(n);++ttxyc)//宏定义
using namespace std;
inline int read()//快读
{
	register int x=0,t=0;register char c=getchar();for(;c<'0'||c>'9';t|=c=='-',c=getchar());
	for(;c>='0'&&c<='9';x=(x<<3)+(x<<1)+(c^48),c=getchar());return t?-x:x;
}
int n,k,a;map<int,int>mmp;
main()
{
	n=read();k=read();
	rpt(n)
	{
		a=read();
		if(!mmp.count(a))mmp[a]=ttxyc;//如果还没有出现过这个数，保存位置
	}
	if(mmp.size()<k)puts("NO");//个数不够
	else
	{
		puts("YES");//足够
		map<int,int>::iterator i=mmp.begin();//设一个指针
		rpt(k)//遍历map
		{
			printf("%d ",i->second+1);//输出位置，因为我喜欢0下标，所以+1
			++i;//这个输出了，下一个
		}
	}
}/**/
```

---

