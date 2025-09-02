# [ARC001A] センター採点

## 题目描述

## AtCoder Regular Contest 001
### A-期中得分
**时间限制 2s， 内存限制 64 MB， 分值 100Pts**
高桥君参加了一次考试，共有$N$题， 所有问题的答案都是$1 - 4$之间的整数。 高桥君考试前并没有复习， 所以全都选了同一选项， 期中考试答案发布后， 高桥不记得自己选了哪个选项了， 但是高桥想知道自己的分数。
请输出高桥最高和最低的得分

## 说明/提示

$1≤N≤100$

# 题解

## 作者：InversionShadow (赞：0)

## AT_arc001_1 [ARC001A] センター採点 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_arc001_1)

### 题目大意：

给你一个长 $n$ 的字符串，仅包含 $1$ 至 $4$ 之间的字符，问哪个字符出现最多，哪个字符出现最少。

### 思路：

可以用桶数组来记录每个字符出现数量，求其最大值与最小值即可。注意：桶数组记录时要把每个字符转换成数字。

### Code:

```cpp
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1e2 + 1;

int n, cnt[MAXN], maxx = -1e9, minn = 1e9;   // 初始求最大值的变量要初始化最小，初始求最小值的变量要初始化最大
string s;

int main() {
  cin >> n >> s;
  for (int i = 0; i < n; i++) {
    cnt[s[i] - '0']++;     // 每个字符出现次数加 1
  }
  for (int i = 1; i <= 4; i++) {
    maxx = max(maxx, cnt[i]);   // 求最大值
    minn = min(minn, cnt[i]);   // 求最小值
  }
  cout << maxx << ' ' << minn << endl;
  return 0;
}

```

### 谢谢观赏！


---

## 作者：myfly (赞：0)

## 提供一种用string存储，count函数统计的方式。
```cpp
//AT45 センター採点
# include <iostream>
# include <algorithm>
# include <string>
using namespace std;
string ch;
int main() {
    int time1,time2,time3,time4;
    int mint,maxt;
    int N; cin>>N;
    cin>>ch;
    time1=count(ch.begin(),ch.end(),'1');
    time2=count(ch.begin(),ch.end(),'2');
    time3=count(ch.begin(),ch.end(),'3');
    time4=N-time1-time2-time3;
    mint=min(time1,min(time2,min(time3,time4)));
    maxt=max(time1,max(time2,max(time3,time4)));
    cout<<maxt<<' '<<mint<<endl;
    return 0;
}
```

---

## 作者：zybnxy (赞：0)

~~看到没人发题解，我来一发~~

 大水题！！
 
 本题可以用字符串string~~~~
 
 思路：先建一个桶，用来存储1->4出现的个数，然后再用maxn和minn存储最大值和最小值，输出即可。
 代码奉上~~~~
 ```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
string s;
int a[5],n,i,len;
int main()
{
	int maxn=-100000000,minn=100000000;//要把最大值设的很小，最小值设的很大，不然会错误。 
	cin>>n>>s;len=s.length();
	for(i=0;i<len;i++)a[s[i]-'0']++;//字符串的ACELL码转数字 
	for(i=1;i<5;i++)
	{
		maxn=max(maxn,a[i]);//求最大值 
		minn=min(minn,a[i]);//求最小值 
	}
	cout<<maxn<<" "<<minn<<endl;//输出 
	return 0;//完了 
}
```

---

## 作者：CZQ_King (赞：0)

## 哇（WA）！沙发我占了
水题一道，但是我错了，因为答案要字符串输入（你用$int/long long$也行）
#### 思路：弄个类似于桶的东西，将答案放进桶然后判断最多的和最少的就行
```cpp
#include<bits/stdc++.h>//头文件
using namespace std;
int a,c[5];//桶
string b;//坑了我一次的东西
int main(){
    cin>>a>>b;
    for(int i=0;i<a;i++)
        c[int(b[i])-int('0')]++;//用ascii码将答案放进桶里
    cout<<max(max(max(c[1],c[2]),c[3]),c[4])<<" ";//最大值（眼花缭乱*1）
    cout<<min(min(min(c[1],c[2]),c[3]),c[4])<<endl;//最小值（眼花缭乱*2）
    return 0;//完美结束
}
```

---

