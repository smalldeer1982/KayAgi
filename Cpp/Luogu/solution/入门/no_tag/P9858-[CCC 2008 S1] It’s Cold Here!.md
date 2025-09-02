# [CCC 2008 S1] It’s Cold Here!

## 题目描述

加拿大的冬天很冷，但有些地方比其他地方更冷。你的任务非常简单，你需要找出加拿大最冷的城市。因此，当给定一个城市及其温度的列表时，你需要确定列表中哪个城市的温度最低，从而找出最冷的城市。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
Saskatoon -20
Toronto -2
Winnipeg -40
Vancouver 8
Halifax 0
Montreal -4
Waterloo -3```

### 输出

```
Winnipeg```

# 题解

## 作者：Loser_Syx (赞：8)

由于不知道输入总数，可以考虑使用 `while(cin>>s)` 进行读入，然后就可以据此进行打擂台比较，答案是最小值。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    string ans, name;
    int sz = 1e7;
    while(cin >> name){
        int x;
        cin >> x;
        if(x < sz){
            sz = x;
            ans = name;
        }
    }
    cout << ans << '\n';
    return 0;
}
```

---

