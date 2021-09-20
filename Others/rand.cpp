mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int>uni(1,10);
//usage uni(rng)
