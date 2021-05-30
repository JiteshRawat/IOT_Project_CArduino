struct path{ 
      char val;
      double  count;
      struct path *next;  
};

struct path *create(char p,double count)
{
  struct path *x= (struct path *)malloc(sizeof(struct path ));
  x->val= p;
  x->count= count;
  x->next= NULL;

  return x; 
}

struct path *push(struct path *h,char v,double c)
{
   struct path *x=h;
   if(h==NULL)
		return create(v,c);        

	h=create(v,c);

	h->next=x;
	return(h);
}

struct path *pop(struct path *h)
{
  if(h==NULL)
	  return NULL;

  Serial.println(h->val);
  struct path *t= h;
  h= h->next; 
  t->next= NULL;
  free(t);
  return(h);// structure path is returned
}

struct path * top= NULL;

void record(char val,double count)
{
  
  top= push(top,val,count);
  Serial.println(top->val);
   
}
