# Mister B and Book Reading

## 题目描述

Mister B once received a gift: it was a book about aliens, which he started read immediately. This book had $ c $ pages.

At first day Mister B read $ v_{0} $ pages, but after that he started to speed up. Every day, starting from the second, he read $ a $ pages more than on the previous day (at first day he read $ v_{0} $ pages, at second — $ v_{0}+a $ pages, at third — $ v_{0}+2a $ pages, and so on). But Mister B is just a human, so he physically wasn't able to read more than $ v_{1} $ pages per day.

Also, to refresh his memory, every day, starting from the second, Mister B had to reread last $ l $ pages he read on the previous day. Mister B finished the book when he read the last page for the first time.

Help Mister B to calculate how many days he needed to finish the book.

## 说明/提示

In the first sample test the book contains $ 5 $ pages, so Mister B read it right at the first day.

In the second sample test at first day Mister B read pages number $ 1-4 $ , at second day — $ 4-11 $ , at third day — $ 11-12 $ and finished the book.

In third sample test every day Mister B read $ 1 $ page of the book, so he finished in 15 days.

## 样例 #1

### 输入

```
5 5 10 5 4
```

### 输出

```
1
```

## 样例 #2

### 输入

```
12 4 12 4 1
```

### 输出

```
3
```

## 样例 #3

### 输入

```
15 1 100 0 0
```

### 输出

```
15
```

# 题解

## 作者：一叶知秋。 (赞：3)

# 主要是考英文

题意：一本书有c页，第一天能看v0页，往后每一天看的页数都比前一天多a页，**但一天最多看的页数是v1**，第二天开始每天都会**复习p页**，问多少天把书看完？

这不用说了，上代码

```cpp
#include<cstdio>
inline int read(){//快读
	int r=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		r=r*10+c-'0';
		c=getchar();
	}
	return r*f;
}
int main(){
	freopen("MrBA.in","r",stdin);
	freopen("MrBA.out","w",stdout);
	int c=read(),v0=read(),v1=read(),a=read(),p=read();
	int s=v0,ans=1;
	while(s<c){//模拟主体
		v0+=a;
		int pp=p;
		if(v0>v1)pp+=v0-v1;//划重点（超过就只能读v1页了）
		s+=v0-pp;
		ans++;//相当于时间戳
	}
	printf("%d",ans);//输出
	return 0;
}
```

---

## 作者：紊莫 (赞：1)

感觉是恶评（橙最多了）。  

# 题意  

模拟（按一定规则）每一天看书和复习，问看完要几天。  

# 分析  

注意到 $1 \le c \le 1000$，所以模拟页数肯定没差。  

因为每天除了读 $\min \left \{v_{0}+a(i-1),v1\right \}$ 页书外，还要复习 $l$ 页，所以每天实际读的页数就是 $\min \left \{v_{0}+a(i-1),v1\right \}-l$。  

 _另外注意第一天需要特判否则会出现负数。_ 

# 代码  

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int c,v0,v1,a,l,ans=0,i=0;
	cin>>c>>v0>>v1>>a>>l;
	c-=min(v0,v1),ans++,i++;//注意第一天需要特判否则会出现负数
	while(c>0)
	{
		c-=min(v0+a*i,v1)-l;
		ans++,i++;
	}
	cout<<ans;
    return 0;
}
```



---

## 作者：Xx_queue (赞：1)

这题是纯模拟题目，难度较为简单，主要是注意阅读量的上限不能超以及看之前重复的内容的页码要减去
```cpp
#include <bits/stdc++.h>
using namespace std;
int c,v0,v1,a,p,day;
int main()
{
	scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&p);//读入 
	c=c-v0;day=1;//第一天看v0 
	if(c<=0)//如果第一天读完了 
	{
		printf("%d",day);//输出 
		return 0;
	}	
	while(c>0)//如果还没读完 
	{
		day++;//加一天 
		int read=v0+(day-1)*a;//计算每天的阅读量 
		if(read>v1) read=v1;//超过上限 
		read=read-p;//减去看之前看过的页数 
		c-=read;
	}
	printf("%d",day);//输出天数 
	return 0;
}
```


---

## 作者：ruruo (赞：0)

# 分析

直接根据题意模拟即可，就是要注意第一天不用复习 $l$ 页。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int c, v0, v1, a, l;
    int ans = 0;
    cin >> c >> v0 >> v1 >> a >> l;
    do{
        ans++;
        c -= min(v0 + a * (ans - 1), v1); // 根据题目中给的公式计算
        if(ans != 1) c += l; // 如果不是第一天，则需要复习
    }while(c > 0);
    cout << ans << endl;
    return 0;
}
```


---

## 作者：fengxiaoyi (赞：0)

### 修改日志

$2022/11/13:$ 对解法进一步的说明。

### 提示

数据范围：$1\le c\le 1000,0\le l\lt v_0\le v_1\le 1000,0\le a\le 1000$。

### 正解

由于数据范围很小，$c$ 最多不超过 $1000$，由于一天至少可以看一页，所以天数肯定 $\le 1000$，考虑模拟。

枚举每一天，将 $c$ 减去这一天应该看的天数 $\min(v_0+a\times(ans-1),v_1)$，其中 $ans$ 是天数，注意当 $ans\ne 1$ 时，$c$ 要再 $+l$（第一天不用复习）。

最后直到 $c\le 0$，输出 $ans$。

#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,v0,v1,a,l,ans; 
int main(){
	scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&l);
	do{
		ans++;
		if(ans==1) c-=min(v0+a*(ans-1),v1);
		else c-=min(v0+a*(ans-1),v1)-l;
	}while(c>0);
	return !printf("%d",ans);
}
```


---

## 作者：Supor__Shoep (赞：0)

这道题似乎少翻译了一个条件，那就是第一天的时候必须看 $v_0$ 页，不过通过样例其实也可以看出来。

首先我们定义天数，已读页数两个变量进行循环，每一次循环记录每一天读的页数，并且增加一次天数，对于重复读的 $l$ 页，我们只需要减去就可以了。这样一直循环直到读的页数大于总页数，得到的天数就是答案了。

真一道水模拟题。

```cpp
#include<bits/stdc++.h>
using namespace std;
int c,v0,v1,a,l;
int main()
{
	cin>>c>>v0>>v1>>a>>l;
	int days=1,reads=v0;//初始化
	while(reads<c)
	{
		int todays=min(v0+a*days,v1);//按照题目的要求得到页数
		reads+=todays,days++,reads-=l;//流程走一遍
	}
	cout<<days;
    return 0;
}
```

---

## 作者：user470883 (赞：0)

## 思路：
评橙都没大问题。

模拟。

第 $i$ 天要看 $\min(v_0+a\times(i-1),v_1)$ 页，同时还需要 $l$ 页。

我们依据题意模拟即可。

那么除第 $1$ 天外每天要读 $\min(v_0+a\times(i-1),v_1)-l$ 页，第一天没有要复习的，直接是阅读 $v_0$ 页。

## AC CODE:
```
#include<bits/stdc++.h>
using namespace std;

int main()
{
	int c,v0,v1,a,p;
	cin >> c >> v0 >> v1 >> a >> p;
	c-=v0;//第一天
  int ans=1;//记录天数
	while(c>0)//while循环模拟
	{
		ans++;//多一天
		c-=min(v0+a*(ans-1),v1)-p;//还剩c页
	}
	cout << ans << endl;//输出答案
	return 0;
}
```
有问题私我。

---

## 作者：wangshi (赞：0)

### 按题意模拟即可。

具体见代码注释。

```c
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int c,v0,v1,a,l,ans=1;//如题所示,ans存答案 
	scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&l);
	c-=v0;//先把第一天减去,所以ans初始值为1 
	for(int i=2;c>0;i++)//循环模拟 
	{
		int s;
		s=min(v0+a*(i-1),v1);//如题所示,求当天读的页数 
		s-=l;//减去复习页数 
		c-=s;//总页数减去当天读的 
		ans++;//答案加一 
	}
	cout<<ans<<endl;
	return 0;//完美结束 
}

```
### 蒟蒻的第三篇题解，望大佬多多指教。

---

## 作者：ZepX_D (赞：0)

## 题意
一个人第 $ i $ 天要看 $  \min(v_0+a\times(i-1),v_0) $ 页书，从第二天开始每天复习 $  l $ 页，问多久可以读完

## 分析
 $ v_0<=v_1 $ 就是说第一天只读 $ v_0 $ 页，之后每天读 $ \min(v_0+a\times(i-1),v_0)-l $ 页

弄明白题意后这就是一道模拟水题了

# code
```cpp
#include<cstdio>
#include<iostream>

using namespace std;

int main()
{
	int c,v0,v1,a,l,ans=1;
	scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&l);
	c-=v0;
	while(c>0) //如果c<0也就是读完了就跳出
	{
		ans++;
		c-=min(v0+a*(ans-1),v1)-l;
	}
	printf("%d",ans);
	return 0;
}
```

## 总结
这个题就是一个阅读理解题(~~其实也不难理解~~)，读懂题意就能**快乐的切水题**了

---

## 作者：梦游的小雪球 (赞：0)

## 梦雪的思路：

- ### 暴力，循环直到把书读完

## AC代码

```
#include<bits/stdc++.h>
using namespace std;
int c,v0,v1,a,p,s=1;//因为把第一天的去掉了,所以s=1
int main(){
	scanf("%d%d%d%d%d",&c,&v0,&v1,&a,&p);
	c-=v0;//去掉第一天读的
	for(int i=1;c>0;i++,s++){
		c-=min(v1,v0+i*a);//v1为上线
		c+=p; //每天复习的
	}
	cout<<s<<endl;//循环的次数，即读书的天数
	return 0;
}
```

各位NOIP加油！

---

