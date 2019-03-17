import junit.framework.TestCase;
import java.util.Random;

public class UrlValidatorTestRandom extends TestCase {


   public UrlValidatorTestRandom(String testName) {
      super(testName);
   }

  
   public void testRandomIsValid()
   {
	   int count = 0;
	   String url = "";
       UrlValidator validator = new UrlValidator(validSchemes);
       Random rand = new Random();
       for(int i = 1; i <= 100; i++) {
           url = validSchemes [rand.nextInt(validSchemes.length)]+"://" + 
        		   validAuthority[rand.nextInt(validAuthority.length)]+
        		   validPort[rand.nextInt(validPort.length)]+
        		   validPath[rand.nextInt(validPath.length)]+
        		   validQuery[rand.nextInt(validQuery.length)];
           if(validator.isValid(url))
        	   count++;
           else
               System.out.println(i+": Test failed -- " + url +" is not a valid URL");
       }
       System.out.println("testRandomIsValid " + count + " of 100 test passed\n");
       assertEquals("testRandomIsValid failed", count, 100); //Fails test in JUnit

   }
   
   public void testRandomIsInvalid()
   {
	   int count = 0;
	   String url = "";
       UrlValidator validator = new UrlValidator();
       Random rand = new Random();
       for(int i = 1; i <= 100; i++) {
           url = invalidSchemes [rand.nextInt(invalidSchemes.length)]+"://" + 
        		   invalidAuthority[rand.nextInt(validAuthority.length)]+
        		   invalidPort[rand.nextInt(invalidPort.length)]+
        		   invalidPath[rand.nextInt(invalidPath.length)]+
        		   validQuery[rand.nextInt(validQuery.length)];
           if(!validator.isValid(url))// Checks that URL is not valid
        	   count++;
           else
               System.out.println(i+": Test failed -- " + url +" is a valid URL");

       }
       System.out.println("testRandomIsInvalid " + count + " of 100 test passed\n");
       assertEquals("testRandomIsInvalid failed", count, 100); //Fails test in JUnit
   }
   
   public void testRandomAllSchemes()
   {
	   int count = 0;
	   String url = "";
       UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       Random rand = new Random();
       for(int i = 1; i <= 100; i++) {
           url = validAndInvalidSchemes [rand.nextInt(validAndInvalidSchemes.length)]+"://" + 
        		   validAuthority[rand.nextInt(validAuthority.length)]+
        		   validPort[rand.nextInt(validPort.length)]+
        		   validPath[rand.nextInt(validPath.length)]+
        		   validQuery[rand.nextInt(validQuery.length)];
           if(validator.isValid(url))
        	   count++;
           else
               System.out.println(i+": Test failed -- " + url +" is a valid URL");

       }
       System.out.println("testRandomAllSchemes " + count + " of 100 test passed\n");
       assertEquals("testRandomAllSchemes failed", count, 100); //Fails test in JUnit
   }
   
   String[] validSchemes = {"http", "https", "ftp"};
   String[] invalidSchemes = {"htp", "http", "", "##", "123"};
   String[] validAndInvalidSchemes = {"http", "https", "ftp", "htp", "ssl", "wss"};
   String[] validAuthority = {"www.google.com", "www.amazon.com", "oregonstate.edu", "1.1.1.1", "whitehouse.gov"};
   String[] invalidAuthority = {"us.a", "dogpile.x", "webcrawler.ooooo", "askjeeves.klklk", ""};
   String[] validPort = {":0",":8080",":443", ":65535",""};
   String[] invalidPort = {"://", ":-100", "65536", ":asdf","1,000,000"};
   String[] validPath = {"/path", "/path/morepath", "","/","/1/2/3/4/"};
   String[] invalidPath = {"/###/", "//////1", "", ":"};
   String[] validQuery = {"?name=bob", "?apple=red",""};  

}
