# 天下一後入れ先出しデータ構造

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tenka1-2013-qualb/tasks/tenka1_2013_qualB_b

 スタックは最も基本的なデータ構造の1つであり、データを後入れ先出し (Last In First Out) の構造で保持するものである。スタックは最初は空で、要素の追加と取り出しができるが、取り出しは追加されたのが遅い順に行われる。

 ある日、天下一株式会社に務めるユウヤ君は、スタックになりきるという仕事を言い渡された。唖然とするユウヤ君を心配するあなたは、以下の形式の入力で与えられる命令の列をユウヤ君の代わりに処理して、後述のような出力を行うプログラムを作成することにした。

- - - - - -

 入力は以下の形式で標準入力から与えられる。

> $ Q $ $ L $ $ query_1 $ $ query_2 $ $ ... $ $ query_Q $

- $ 1 $ 行目は、与えられる命令の数 $ Q $ ($ 1\ \leq\ Q\ \leq\ 10^5 $) と スタックのサイズ $ L $ ($ 1\ \leq\ L\ \leq\ 2147483647 $) が空白区切りで与えられる。
- $ 2 $ 行目から $ Q+1 $ 行目までの $ Q $ 行は、$ i $ ($ 1\ \leq\ i\ \leq\ Q $) 番目の 命令が与えられる。

 各命令は、以下 $ 4 $ 種類のうちいずれかに該当する。

1. Push $ N $ $ M $

- スタックに要素 $ M $ を $ N $ 個追加する。出力は行わない。

10. Pop $ N $
- スタックから要素を $ N $ 個取り出す。出力は行わない。

12. Top
- スタックの先頭要素を $ 1 $ 行で出力する。この命令でスタックを構成する要素は変更されない。

14. Size
- スタックの要素数を $ 1 $ 行で出力する。

$ N $, $ M $ はそれぞれ整数で、 $ 1\ \leq\ N\ \leq\ 10^5 $, $ -2^{20}\ \leq\ M\ \leq\ 2^{20} $ をみたす。

ただし、スタックの先頭要素とは、スタックの要素のうちで最後に追加されたものであり、もしそのときPop $ 1 $を行ったとすると取り出される要素である。

- $ Q\ \leq\ 50 $, $ N\ \leq\ 50 $ の入力に正解すると、$ 60 $ 点満点に対して部分点として、$ 30 $ 点が与えられる。

 上記のとおり、与えられた命令を順番に処理していき、Top、またはSizeの入力が与えられた際に出力を行う。

 ただし、以下の $ 3 $ つの場合、スタックは例外を投げて止まってしまう。

- Push $ N $ $ M $ を要素数が $ L-N $ より大きいスタックに対して行った場合
- Pop $ N $を要素数が $ N $ 未満のスタックに対して行った場合
- Top を空のスタックに対して行った場合

 スタックが投げる例外は以下の通りである。

- Push による例外でプログラムが終了した場合は `FULL`
- Pop または Top による例外でプログラムが終了した場合は `EMPTY`

 これらの例外は $ 1 $ 行で出力され、例外を投げた後のスタックはそれ以降の命令を放棄する。  
 スタックは最後まで正常に命令を処理できた場合、 `SAFE` を $ 1 $ 行で出力して終了する。

 ```

7 20
Push 2 3
Push 4 5
Top
Size
Pop 5
Top
Size
```

 ```

5
6
3
1
SAFE
```

 ```

1 10
Push 40 40
```

 ```

FULL
```

 ```

5 10
Push 1 2
Top
Pop 1
Top
Size
```

 ```

2
EMPTY
```

 ```

4 10
Top
Size
Push 1 1
Top
```

 ```

EMPTY
```

# 题解

## 作者：fourGS (赞：0)

問題概要

模拟堆栈的问题。
但是，可以使用一条指令插入很多相同的数字或弹出很多。
此外，回答堆栈中数字数量和堆栈顶部元素的查询是混合的。
另外，栈的大小是固定的，如果超出大小，或者从空栈中弹出或者引用栈顶元素，就会报错并停止。
有关详细信息，请参阅问题文本。

解法

只做模拟。
加多了，一个一个做就是TLE。
注意溢出，因为堆栈的大小达到了可以用带符号的 32 位整数表示的限制。（使用 64 位整数更容易，不用担心。）


C++源代码：
```c
#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<string>
#include<utility>
#include<iostream>
#include<cmath>
#include<cassert>
using namespace std;

#define REP(i,a,b) for(i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)

#define ll long long

ll read_int(ll mn, ll mx, char next){
  ll c, fg = 1, res = 0;
  c=getchar();
  if(c=='-') fg = -1, c = getchar();
  assert('0'<=c && c<='9');
  res = c - '0';
  for(;;){
    c = getchar();
    if(c==next) break;
    assert(res!=0);
    assert('0'<=c && c<='9');
    res = res * 10 + (c - '0');
  }
  res *= fg;
  assert(mn<=res && res<=mx);
  return res;
}

string read_string(int mx_len, char *next){
  int c;
  string res;

  for(;;){
    c = getchar();
    if(c==' ' || c=='\n'){ *next = c; break; }
    assert(c != EOF);
    res += c;
    assert( res.size() <= mx_len );
  }

  return res;
}


int main(){
  int Q; ll L;

  int i, j, k;
  static int st[100000], num[100000]; int depth; ll size;
  string query;
  int N, M;
  int fin = 0;
  char c;

  Q = read_int(1, 100000, ' ');
  L = read_int(1, 2147483647, '\n');

  depth = size = 0;

  while(Q--){
    query = read_string(10, &c);
    if(query == "Push"){
      assert(c == ' ');
      N = read_int(1, 100000, ' ');
      M = read_int(-(1<<20), 1<<20, '\n');
      if(fin) continue;
      if(size + N > L){ fin = 2; continue; }
      st[depth] = M;
      num[depth] = N;
      size += N;
      depth++;
    } else if(query == "Pop"){
      assert(c == ' ');
      N = read_int(1, 100000, '\n');
      if(fin) continue;
      if(size < N){ fin = 1; continue; }
      size -= N;
      while(N && num[depth-1] <= N){
        N -= num[depth-1];
        depth--;
      }
      if(N) num[depth-1] -= N;
    } else if(query == "Top"){
      assert(c == '\n');
      if(fin) continue;
      if(size==0){ fin=1; continue; }
      printf("%d\n",st[depth-1]);
    } else if(query == "Size"){
      assert(c == '\n');
      if(fin) continue;
      printf("%d\n", size);
    } else {
      assert(0);
    }
  }

  if(fin==0) puts("SAFE");
  if(fin==1) puts("EMPTY");
  if(fin==2) puts("FULL");

  {
    char c;
    assert( scanf("%c",&c)!= 1 );
  }
  return 0;
}
```


  
  
  
  完！

---

