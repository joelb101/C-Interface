int Arith_max(int x,int y){
	return x>y?x:y;
}

int Arith_min(int x,int y){
	return x<y?x:y;
}

int Arith_div(int x,int y){
	if(-11/2 == -5 && (x<0) != (y<0)){
		return x/y-1;
	}
	return x/y;
}

int Arith_mod(int x,int y){
	return x-y*Arith_div(x,y);
}

int Arith_floor(int x,int y){
	return Arith_div(x,y);
}

int Arith_ceil(int x,int y){
	return Arith_div(x,y) + (x%y != 0);
}
