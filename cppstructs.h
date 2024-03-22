#ifndef HEADER_1406BB8A86FC6F38
#define HEADER_1406BB8A86FC6F38

#endif // header guard

#include <bits/stdc++.h>

using namespace std;

struct DSU {
private:
	vector<int> t;
public:
	DSU(int n = 1e5) {
		t.resize(n);
		for(int i = 0; i < n; i++)
			t[i] = i;
	}

	int parent(int x) {
		if(x == t[x])
			return x;
		else
			return t[x] = parent(t[x]);
	}

	void join(int x, int y) {
		int tx = parent(x), ty = parent(y);
		t[tx] = t[ty];
	}

	void clear() {
		for(int i = 0; i < t.size(); i++)
			t[i] = i;
	}

	bool sameparent(int x, int y) {
		return (parent(x) == parent(y));
	}
};

struct MATRIX {
private:
	int lin = 0, col = 0, mod = 0;
public:
	vector<vector<int>> mat;

	MATRIX(int l, int c, int kmod = 1e9 + 7) {
		lin = l;
		col = c;
		mod = kmod;
		mat.resize(lin, vector<int>(col, 0));
	}

	const MATRIX operator *(const MATRIX &other) {
		if(col == other.lin) {
			MATRIX rez(lin, other.col);

			for(int i = 0; i < lin; i++) {
				for(int j = 0; j < other.col; j++) {
					for(int l = 0; l < col; l++) {
						rez.mat[i][j] = (long long)((long long)rez.mat[i][j] + (long long)mat[i][l] * other.mat[l][j]) % mod;
					}
				}
			}

			return rez;
		}
	}
};

struct Trie {
private:
	struct Node {
		int apar = 0, cuv = 0;
		vector<Node *> fii;

		Node() {
			fii.resize(26, nullptr);
		}
	};

	Node * root = nullptr;

	Node * insert_(Node * node, const char * s) {

		if(node == nullptr)
			node = new Node;

		node->apar++;
		if(s[0] == '\0')
			node->cuv++;
		else
			node->fii[s[0] - 'a'] = insert_(node->fii[s[0] - 'a'], s + 1);

		return node;
	}

	Node * delete_(Node * node, const char * s) {

		if(node == nullptr)
			return node;

		node->apar--;
		if(s[0] == '\0')
			node->cuv--;
		else
			node->fii[s[0] - 'a'] = delete_(node->fii[s[0] - 'a'], s + 1);

		if(node->apar == 0) {
			delete node;
			node = nullptr;
		}

		return node;
	}

	int query_apar(Node * node, const char * s) {

		if(node == nullptr)
			return 0;

		if(s[0] == '\0')
			return node->cuv;
		else
			return query_apar(node->fii[s[0] - 'a'], s + 1);
	}

	int query_pref(Node * node, const char * s) {

		if(node == nullptr)
			return 0;

		if(s[0] == '\0' || (node->fii[s[0] - 'a'] == nullptr))
			return 0;
		else
			return query_pref(node->fii[s[0] - 'a'], s + 1) + 1;
	}
public:
	void Delete(string s) {
		root = delete_(root, s.c_str());
	}

	int Count(string s) {
		return query_apar(root, s.c_str());
	}

	void Insert(string s) {
		root = insert_(root, s.c_str());
	}

	int PrefMax(string s) {
		return query_pref(root, s.c_str());
	}
};

struct BATOG {
private:
	int bkSize, length;

	vector<int> bat, dir;
public:
	BATOG(int nmax = 1e5, int sz = 512) {
		bkSize = sz;
		bat.resize(nmax / sz + 3);
		dir.resize(nmax / sz + 3);
		length = nmax / sz;
	}

	void build(vector<int> &a, int n) {
		for(int i = 0; i < n; i++)
			bat[i / bkSize] = 0;
		for(int i = 0; i < n; i++)
			bat[i / bkSize] = max(bat[i / bkSize], a[i]);
	}

	void print() {
		for(int i = 0; i < length; i++)
			cout << bat[i] << " ";
	}

	void updatePoz(vector<int> &a, int val, int poz) {
		poz--;
		a[poz] = val;
		dir[poz / bkSize] = 1;
	}

	void updateBuckets(vector<int> &a) {
		for(int i = 0; i < length; i++) {
			if(dir[i]) {
				updateBucket(a, i);
				dir[i] = 0;
			}
		}
	}

	void updateBucket(vector<int> &a, int bucket) {
		int val = bucket * bkSize, lval = val + bkSize - 1;
		bat[bucket] = 0;
		for(int i = val; i <= lval; i++)
			bat[bucket] = max(bat[bucket], a[i]);
	}

	int query(vector<int> &a, int x, int y) {
		x--;
		y--;
		int fBucket = x / bkSize + 1, lBucket = y / bkSize - 1;
		int fBucketPoz = fBucket * bkSize, lBucketPoz = (lBucket + 1) * bkSize - 1;
		int rez = 0;
		updateBuckets(a);
		if(lBucket - fBucket >= 2) {
			for(int i = x; i < fBucketPoz; i++)
				rez = max(rez, a[i]);
			for(int i = lBucketPoz + 1; i <= y; i++)
				rez = max(rez, a[i]);
			for(int i = fBucket; i <= lBucket; i++)
				rez = max(rez, bat[i]);
		} else {
			for(int i = x; i <= y; i++)
				rez = max(rez, a[i]);
		}
		return rez;
	}
};

struct AIB {
private:
#define lsb(x) (x&(-x))
	vector<int> aib;
	int n;

	int queryPref(int poz) {
		int s = 0;
		for(; poz > 0; poz -= lsb(poz))
			s += aib[poz];
		return s;
	}
public:
	AIB(int N) {
		n = N;
		aib.resize(n + 1);
	}

	void update(int poz, int val) {
		for(; poz <= n; poz += lsb(poz))
			aib[poz] += val;
	}

	int query(int st, int dr) {
		return queryPref(dr) - queryPref(st - 1);
	}

	int binsearch(int x) {
		int s = 0, ans = 0;
		for(int i = 24; i >= 0; i--) {
			if(ans + (1 << i) <= n && s + aib[ans + (1 << i)] < x) {
				s += aib[ans + (1 << i)];
				ans += (1 << i);
			}
		}
		ans++;
		if(ans > n || queryPref(ans) != x)
			return -1;
		else
			return ans;
	}
};
