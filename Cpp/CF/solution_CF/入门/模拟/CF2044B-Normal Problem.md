# Normal Problem

## 题目描述

玻璃上写着一串仅包含小写字母 $p$，$q$，$w$ 的字符串 $a$。求该玻璃水平翻转之后，从左到右看到的新字符串 $b$。

## 样例 #1

### 输入

```
5
qwq
ppppp
pppwwwqqq
wqpqwpqwwqp
pqpqpqpq```

### 输出

```
pwp
qqqqq
pppwwwqqq
qpwwpqwpqpw
pqpqpqpq```

# 题解

## 作者：sccc_ (赞：0)

## solution

进商店后字符串是倒着的，$p$ 会变成 $q$，$q$ 会变成 $p$，$w$ 不变。

***

## code
```c++
#include <bits/stdc++.h>
using namespace std;

int t;

int main()
{
    cin >> t;
    while (t --)
    {
        string s;
        cin >> s;
        for (int i = s.size() - 1; i >= 0; i --)
        {
            if (s[i] == 'q')
                cout << 'p';
            else if (s[i] == 'p')
                cout << 'q';
            else
                cout << 'w';
        }
        cout << '\n';
    }
    return 0;
} 
```

---

## 作者：wuyouawa (赞：0)

### 题目大意

有一串由字符 $p$、$q$ 和 $w$ 组成的字符串，涂在商店的玻璃窗上。船经过商店，站在玻璃窗前，观察到字符串 $a$。然后船进入商店，直接看向同一块玻璃窗，观察到字符串 $b$。

船给了你字符串 $a$。你的任务是找出并输出字符串 $b$。

### 思路

首先我们~~通过常识~~可以知道进入商店后的字符串是与原来的反过来的，而且 $p$ 会变成 $q$，$q$ 会变成 $p$。

那么直接按这些处理即可，注意多测换行。

### 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t;
string s;
signed main(){
	cin>>t;
	while(t--)
	{
		cin>>s;
		for(int i=s.size()-1;i>=0;i--)//反过来
		{
			if(s[i]=='p')  cout<<'q';//p变q
			else  if(s[i]=='q') cout<<'p';//q变p
			else  cout<<'w';//w不变
		}
		cout<<endl;//多测换行
	}
	return 0;
}
```

---

