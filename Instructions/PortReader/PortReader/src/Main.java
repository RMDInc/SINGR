
/*
 * Copyright (c) 1995, 2013, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *   - Neither the name of Oracle or the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

public class Main 
{  
	public static boolean running = true;
	public static IntBuffer intBuf;
	public static final int BUFFER_SIZE = 20;
	public static byte[] byteBuffer = new byte[17*4*BUFFER_SIZE ];
	public static byte[] byteBuffer2 = new byte[20];
	public static int[] eventBuffer = new int[17*BUFFER_SIZE ];
	public static int counts = 0;
	public static void main(String [] args)
	{
		while(running)
		{
			try {
				dataLoop();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
    public static void dataLoop() throws IOException, InterruptedException 
    {
        String hostName = "192.168.250.2";
        int portNumber = 7;
    	
        try (
            	Socket echoSocket = new Socket(hostName, portNumber);
            	PrintWriter out = new PrintWriter(echoSocket.getOutputStream(), true);
            ) {
        		echoSocket.setSoTimeout(100);
                while (running) 
                {
            		out.println("1");
            		//echoSocket.getInputStream().read(byteBuffer);
            		//echoSocket.getInputStream().read(byteBuffer2);
					//intBuf = ByteBuffer.wrap(byteBuffer).order(ByteOrder.LITTLE_ENDIAN).asIntBuffer();
            		//intBuf.get(eventBuffer);
            		System.out.println(echoSocket.getInputStream().read());
            		//printArray(eventBuffer);
            		//System.out.println("*********************************************************");
                }
            } catch (UnknownHostException e) {
                System.err.println("Don't know about host " + hostName);
                System.exit(1);
            } catch (IOException e) {
                System.err.println("Couldn't get I/O for the connection to " + hostName);
            } 
    }
    static void printArray(int[] eventBuffer)
    {
    	for(int i = 0; i < 17 * BUFFER_SIZE ; i++)
    	{
			System.out.print(eventBuffer[i] + "\t");
			if((i+1)%17 == 0)
			{
				System.out.println();
			}
    	}
    	
    }
}