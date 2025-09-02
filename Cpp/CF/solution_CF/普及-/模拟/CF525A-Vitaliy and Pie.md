# Vitaliy and Pie

## 题目描述

After a hard day Vitaly got very hungry and he wants to eat his favorite potato pie. But it's not that simple. Vitaly is in the first room of the house with $ n $ room located in a line and numbered starting from one from left to right. You can go from the first room to the second room, from the second room to the third room and so on — you can go from the ( $ n-1 $ )-th room to the $ n $ -th room. Thus, you can go to room $ x $ only from room $ x-1 $ .

The potato pie is located in the $ n $ -th room and Vitaly needs to go there.

Each pair of consecutive rooms has a door between them. In order to go to room $ x $ from room $ x-1 $ , you need to open the door between the rooms with the corresponding key.

In total the house has several types of doors (represented by uppercase Latin letters) and several types of keys (represented by lowercase Latin letters). The key of type $ t $ can open the door of type $ T $ if and only if $ t $ and $ T $ are the same letter, written in different cases. For example, key f can open door F.

Each of the first $ n-1 $ rooms contains exactly one key of some type that Vitaly can use to get to next rooms. Once the door is open with some key, Vitaly won't get the key from the keyhole but he will immediately run into the next room. In other words, each key can open no more than one door.

Vitaly realizes that he may end up in some room without the key that opens the door to the next room. Before the start his run for the potato pie Vitaly can buy any number of keys of any type that is guaranteed to get to room $ n $ .

Given the plan of the house, Vitaly wants to know what is the minimum number of keys he needs to buy to surely get to the room $ n $ , which has a delicious potato pie. Write a program that will help Vitaly find out this number.

## 样例 #1

### 输入

```
3
aAbB
```

### 输出

```
0
```

## 样例 #2

### 输入

```
4
aBaCaB
```

### 输出

```
3
```

## 样例 #3

### 输入

```
5
xYyXzZaZ
```

### 输出

```
2
```

# 题解

## 作者：落河之秋 (赞：1)

### 题目大意

给定一个字符串，其中小写字母与大写字母**交替**出现，每出现一个大写字母如果前面有对应的小写字母则将其扣除，若没有则花费一次~~开挂~~次数获得一个小写字母，问一共要开几次挂。~~这翻译实在过于生草~~

### 分析

我一看到这题脑子里就瞬间想到了 STL 库里一个非常神奇的容器，那就是：**map** ！！！


我们可以建立一个 char 类型与 int 类型互相映射的 map 来存储小写字母所出现的次数，也就是用 map 来进行桶排序，如果桶为空，则次数加一。

分析完毕，实现过程奉上。


### 代码

```cpp
#include<iostream>
#include<string>
#include<map> //使用map需调用map库

using namespace std;

int n,ans = 0;
string s;
map<char,int> a;

int main()
{
	cin>>n>>s;
	
	for(int i=0; i<=(2 * n - 2) - 1; i++)
	{
		if(s[i] >= 'a' and s[i] <= 'z') //存储小写字母出现次数
		{
			a[s[i]]++;
		}
	}
	for(int i=0; i<=(2 * n - 2) - 1; i++)
	{
		if(s[i] >= 'A' and s[i] <= 'Z')
		{
			if(a[s[i]] != 0) //当桶不为空时，存储的数目减一
			{
				a[s[i]]--;
			}
			else //反之累加次数
			{
				ans++;
			}
		}
	}
	cout<<ans;
	
	return 0;
}
```
 ### _**be brought to successful completion.**_

---

## 作者：joy2010WonderMaker (赞：1)

### 解题思路

可以用一个桶去存储拿到过的钥匙。因为只有26种钥匙，所以只需要定义一个长度为26的桶即可。有就将那种钥匙的数量减1，没有就将还需要的钥匙数加1。

### 代码

```cpp
#include<cstdio>
int have[26],ans;//have数组就是桶，统计出现次数
char h[200005];//存储字符串
int main(){
    int n;
    scanf("%d",&n);
    scanf("%s",&h);
    for(int i=0;i<2*n-2;i++){
        if(i%2==0)have[h[i]-'a']++;//统计出现次数
        else{
            if(have[h[i]-'A'])have[h[i]-'A']--;//如果有，就将那种钥匙数减1
            else ans++;//如果没有，就将需要的钥匙数加1
        }
    }
    printf("%d",ans);
    return 0;
}
```


---

## 作者：chufuzhe (赞：1)

这道题有一个很显然的贪心结论：钥匙能用就用，用反证法可以证明。

所以可以用桶实现，统计每个钥匙的数量，开门的时候如果有就把这种钥匙数量减一，没有就把还需要的钥匙数量增加一。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t[30]; //桶
int main()
{
	int n, ans = 0;
	cin >> n;
	for(int i = 1; i < n; i++) {
		char a, b;
		cin >> a >> b;
		t[a - 97]++; //a钥匙数量增加1
		if(t[b - 65] > 0) t[b - 65]--; //用了b钥匙
		else ans++; //没有b钥匙，还需要的钥匙数量增加1
	}
	cout << ans << endl;
	return 0;
}

```


---

## 作者：zhaoyp (赞：1)

## 大体思路：

用一个数组记录现有每种钥匙的数量，若遇到钥匙，则将它存到数组中。每次遇到门，判断是否有这种钥匙，若没有，则将答案加 $1$ 。

### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans,a[155];
string str;
void input()
{
	scanf("%d",&n);
	cin >> str;
}
void work()
{
	for(int i = 1;i < n;i++)
	{
		a[str[i * 2 - 2] - 'a']++;
		if(a[str[i * 2 - 1] - 'A'])	
			a[str[i * 2 - 1] - 'A']--;
		else
			ans++;
	}
}
void output()
{
	printf("%d",ans);
}
int main()
{
	input();
	work();
	output();
	return 0 ;
}
```

---

## 作者：小恐 (赞：0)

~~这题好像非常简单的样子。~~

~~就是我最后一个样例数错了，还以为是我看错题了，结果看了好几遍题意（这对一个英语蒟蒻很不友好）。~~

这题意思是有一个$2\times n-2$的字符串，保证是小写大写交替出现（第一个是小写字母）。小写字母表示你捡到了一把钥匙，大写字母表示你遇到了一扇门。这一扇门可以用之前捡到的钥匙开，但开完门后钥匙就失效了，也可以花钱买一把钥匙。问你最少买几把钥匙。

非常显然，如果此时你有开这扇门的钥匙，那就用吧，~~正确性显然~~。

上代码：
```cpp
#include<stdio.h>
using namespace std;
char a[200005];
int cnt[27];
int ans;
int main()
{
	int n;
	scanf("%d%s",&n,a);
	for(int i=0;a[i]!='\0';++i)
	{
		if(a[i]>='a'&&a[i]<='z')
			++cnt[a[i]-'a'];
		else
		{
			if(cnt[a[i]-'A'])
				--cnt[a[i]-'A'];
			else
				++ans;
		}
	}
	printf("%d",ans);
	return 0;
}
```
[别说我没过](https://www.luogu.com.cn/record/30816821)

---

