# Is your horseshoe on the other hoof?

## 题目描述

有匹叫Valera的马要和朋友一起去参加聚会。

他一直关注时尚，知道穿不同颜色的马蹄铁非常流行。

去年Valera有四个马蹄铁留下来了，但也许有些颜色相同。在这种情况下，他需要去商店买更多的马蹄铁，让他不在他时髦的同志面前丢脸。

幸运的是，有家商店出售各种颜色的马蹄铁，且Valera有足够的钱购买四种。然而，为了省钱，他想花尽可能少的钱，所以你需要帮助Valera，并确定他至少需要买多少马蹄铁来保证他有四种不同颜色的马蹄铁去参加派对。

## 样例 #1

### 输入

```
1 7 3 3
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 7 7 7
```

### 输出

```
3
```

# 题解

## 作者：引领天下 (赞：7)

这题怎么没人做呢……

其实看了我的[翻译](https://www.luogu.org/discuss/show?postid=43551)就知道是求4个数里有几个重复的-1

所以很简单了

代码很短就不写注释了

```cpp
#include <bits/stdc++.h>
using namespace std;
int a[4],ans;
int main(void){
    scanf ("%d%d%d%d",&a[0],&a[1],&a[2],&a[3]);
    sort (a,a+4);
    for (int i=1;i<4;i++)if (a[i]==a[i-1])ans++;
    printf ("%d",ans);
}
```

---

## 作者：wanghy989 (赞：5)

## 一行最短代码！！！

```python
print(4 - len(set(input().split())))

# 1、集合去重。
# 2、用 4 （马蹄铁总数）减去集合长度。
```



---

## 作者：温情 (赞：2)

这道题的思路其实就是...输入四个数找它们中有几个相同的数,输出**相同的数有几组**即可.

但是...作为蒟蒻就应该有~~蒟蒻~~的思路.

使用一个字符串存储输入.

因为输入之间是有空格的.

所以分四次读入.

新读入一个字符时判断字符串中是否有这个字符.

有就代表找到了新的一组相同的数，没有就把字符存入字符串.最后输出找到的相同的数有几组即可.

附上代码:

```
#include<bits/stdc++.h>
using namespace std;
int main()
{
	string str="",tmp;
	int ans=0;
	for(int i=0;i<4;i++)
	{
		cin>>tmp;
		if(str.find(tmp)==string::npos)
			str+=tmp;
		else
			ans++;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：oizys (赞：1)

```cpp
#include<iostream>
#include<algorithm>
#include<set>
using namespace std;
int main(){
	int a;
	set<int>s;
	for(int i=0;i<4;i++){
		cin>>a;
		s.insert(a);
	}
	cout<<4-s.size()<<endl;
	return 0;
}

```

---

