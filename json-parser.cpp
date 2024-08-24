#include <cstdlib>
#include <json-c/json_types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

struct jobjs {
    json_object* jname;
    json_object* jage;
    json_object* jemail;
    json_object* jbalance;
};

struct persondata {
    char* name;
    char* age;
    char* email;
    char* balance;
};

int
main(void)
{
   persondata pd;
   jobjs jd;
   json_object *root = json_object_from_file("test.json");
   if (!root)
       return 1;

   jd.jname = json_object_object_get(root,  "name");
   jd.jage = json_object_object_get(root,  "age");
   jd.jemail = json_object_object_get(root,  "email");
   jd.jbalance = json_object_object_get(root,  "balance");
   // Store the string values of these json_objects in our char arrays
   pd.name = strdup(json_object_get_string(jd.jname));
   pd.age = strdup(json_object_get_string(jd.jage));
   pd.email = strdup(json_object_get_string(jd.jemail));
   pd.balance = strdup(json_object_get_string(jd.jbalance));
   // Lose ownership of our json_objects first_name and last_name
   json_object_put(root);
   // Verify our char arrays still have the proper values
   printf("%s, %s, %s, %s\n", pd.name, pd.age, pd.email, pd.balance);
   // Cleanup
   free(pd.name);
   free(pd.age);
   free(pd.email);
   free(pd.balance);
   return 0;
}
