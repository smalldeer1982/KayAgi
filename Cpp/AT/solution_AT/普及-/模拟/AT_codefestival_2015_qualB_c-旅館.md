# 旅館

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2015-qualb/tasks/codefestival_2015_qualB_c

高橋君は部屋が $ N $ 室ある旅館を経営しています。今日は $ M $ 組の予約が入っていますが、全ての予約を適切に部屋に割り振ることができるかを確認していませんでした。各予約について、その組の人数以上の定員の部屋を割り振る必要があります。各予約について必ず $ 1 $ つの部屋が割り当てられる必要があり、$ 1 $ つの予約について複数の部屋を割り当てたり、複数の予約を $ 1 $ つの部屋に割り当てたりすることはできません。全ての予約に部屋を割り振ることができるならば `YES` を、割り振ることができないならば `NO` を出力してください。

## 说明/提示

### 部分点

この問題には部分点が設定されている。

- $ N\ ≦\ 100 $, $ M\ ≦\ 100 $ を満たすデータセットに正解した場合は、$ 60 $ 点が与えられる。
- 追加の制約のないデータセットに正解した場合は、上記とは別に $ 40 $ 点が与えられる。

## 样例 #1

### 输入

```
3 2
2 2 3
3 1```

### 输出

```
YES```

## 样例 #2

### 输入

```
3 2
2 2 3
3 3```

### 输出

```
NO```

## 样例 #3

### 输入

```
3 4
10 10 10
1 1 1 1```

### 输出

```
NO```

## 样例 #4

### 输入

```
10 10
10 9 8 7 6 5 4 3 2 1
10 9 8 7 6 5 4 3 2 1```

### 输出

```
YES```

# 题解

## 作者：ailo (赞：2)

//作为第一个AC这道题的蒟蒻，，发一篇小题解，，希望能过

主要是容易超时，把双层循环换成指针就好了

数据提前要排序，，为后面的处理做准备

大概就这样，上代码：

````

#include<iostream>
  
#include<algorithm>
  
using namespace std;
  
int n,m;
  
int a[100010],b[100010];
  
int cmp(int x,int y){
  
	return x>y;
  
}
  
int main(){
  
	cin>>n>>m;
  
	for(int i=1;i<=n;i++)
                         
	cin>>a[i];
  
	for(int i=1;i<=m;i++)
                         
	cin>>b[i];
  
	sort(a+1,a+n+1,cmp);
  
	sort(b+1,b+m+1,cmp);
  
	int h=1;
  
	for(int i=1;i<=n;i++){
                          
		if(a[i]>=b[h]){
  
			b[h]=-1;
  
			h++;
  
			if(h>m) break;
  
		}
  
	}
  
	for(int i=1;i<=m;i++){
                          
		if(b[i]!=-1){
                          
			cout<<"NO"<<endl;
                             
			return 0;
                             
		}
                             
	}
                             
	cout<<"YES"<<endl;
                      
	return 0; 
}
``````

---

## 作者：shenmadongdong (赞：0)

这题实际上并不需要排序。。。

首先我们知道如果对于某一个数字 $x$ ，房间最大人数比它多的房间没有组内人数比它多的组多，就一定输出`NO`，否则输出`YES`

那么统计房间最大人数出现次数与组内人数出现次数，做一遍后缀和，全部比较一遍，如果有某个下标前者比后者小就输出`NO`，这可以压在一个数组内进行

代码很短，时间复杂度也很低：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100010],x;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>x,a[x]++;
	for(int i=1;i<=m;i++) cin>>x,a[x]--;
	for(int i=100000;i>=0;i--) if ((a[i]+=a[i+1])<0) return puts("NO"),0;
	puts("YES");
	return 0;
}
```

---

## 作者：二分之一 (赞：0)

这道题是真的坑。。。

一，翻译有误，应该为“必须分配不低于该组人数的名额的房间”

二，格式（必须有换行）。。。

不多说了，看代码吧

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100001],b[100001]; 
bool s[100001];
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);//输入每个房间的最大人数
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&b[i]);//输入每组的人数
	}
	sort(a+1,a+n+1);
	sort(b+1,b+m+1);//排个序，下面用
	if(m>n)
	{
		printf("NO\n");
		return 0;
	}
        //如果组数大于房间数，肯定不能给所有分配，所以直接输出NO
	int t=m;
	for(int i=n;i>=1;i--)
	{
		if(a[i]>=b[t])
		{
			s[t]=1;
            //房间和组都是从大到小遍历,第t个组能住就记录下来
			t--;
			if(t<=0) break;//所有组遍历完了就退出，节约时间
		}
	}
	for(int i=1;i<=m;i++)
	    if(s[i]==0)//有一个组不能住就输出NO
	    {
	    	printf("NO\n");
	    	return 0;
	    }
	printf("YES\n");
	return 0;
}
```

---

