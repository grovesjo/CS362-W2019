
import junit.framework.TestCase;
import java.util.Scanner;


public class UrlValidatorTestManual extends TestCase {


   public UrlValidatorTestManual(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing
	   // get user data
	   Scanner scanObj = new Scanner(System.in);
	   System.out.print("Enter test Url: ");
	   String testUrl = scanObj.nextLine();
	   
	   // set up options and create url validator objects
	   long options = UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES
			   + UrlValidator.ALLOW_LOCAL_URLS + UrlValidator.NO_FRAGMENTS;
	   UrlValidator defaultVldtr = new UrlValidator(null, null, 0);
	   UrlValidator allOptVldtr = new UrlValidator(null, null, options);
	   
	   // set up initial values for return and print the url being tested
	   boolean defRetVal = false;
	   boolean allOptRetVal = false;
	   System.out.println("testing: '" + testUrl + "'");
	   
	   // test isValid() with the default UrlValidator
	   try
	   {
		   System.out.print("default: ");
		   defRetVal = defaultVldtr.isValid(testUrl);
		   System.out.println(defRetVal);
	   }
	   catch (Error er1)
	   {
		   System.out.println("Error caught: " + er1);
		   System.out.println("Cause: " + er1.getCause());
	   }
	   
	   // test isValid() when all options are turned on
	   try
	   {
		   System.out.print("all options: ");
		   allOptRetVal = allOptVldtr.isValid(testUrl);
		   System.out.println(allOptRetVal);
	   }
	   catch (Error er2)
	   {
		   System.out.println("Error caught: " + er2);
		   System.out.println("Cause: " + er2.getCause());
	   }

	   
	   // close scanner object
	   scanObj.close();
	   
   }
     

}
