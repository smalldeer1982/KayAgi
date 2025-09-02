# 自由研究

## 题目描述

[problemUrl]: https://atcoder.jp/contests/kupc2013/tasks/kupc2013_g



# 题解

## 作者：wzm2007 (赞：3)

    #include<iostream>
    using namespace std;
    int main()
    {
        cout<<3<<endl<<"NYY\n"<<"YNY\n"<<"YYN\n"; 
        return 0;
    }

---

## 作者：yazzkl (赞：1)

此题，只要搞懂一个东西，那就是何谓无向图邻接矩阵（不懂的可以自行baidu）

然后就可以读懂题意。。。

其次，在AT上可以观察样例。找到规律

最后谁都会——————打表！！！！（n过水，可以试一试）

就轻轻松松切掉黑题

```
#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <complex>
#include <set>
#include <map>
#define rep(i,n) for(int i = 0; i < (int)(n); i++)

using namespace std;

int main(){
    puts("40");
    puts("NYYYYYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");

    puts("YNNNNNNYYYYYNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    puts("YNNNNNNNNNNNYYYYYNNNNNNNNNNNNNNNNNNNNNNN");
    puts("YNNNNNNNNNNNNNNNNYYYYYNNNNNNNNNNNNNNNNNN");
    puts("YNNNNNNNNNNNNNNNNNNNNNYYYYYYNNNNNNNNNNNN");
    puts("YNNNNNNNNNNNNNNNNNNNNNNNNNNNYYYYYYNNNNNN");
    puts("YNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYYYYYY");

    rep(i,5) puts("NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    rep(i,5) puts("NNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    rep(i,5) puts("NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    rep(i,6) puts("NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    rep(i,6) puts("NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
    rep(i,6) puts("NNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
}


```

---

## 作者：rui_er (赞：1)

# 打表题解

还好在 ```AtCoder``` 有一个账号，在上面找到一个样例，直接输出（方法好不好？）。

下面是程序代码（C++）：

```cpp
#include <iostream>
using namespace std;

namespace ans
{
	inline void output()
    {
    	cout<<"3\nNYY\nYNY\nYYN"<<endl;
    }
}

int main(int arch, char**arcv)
{
    ans::output();
    return 0;
}
```

---

