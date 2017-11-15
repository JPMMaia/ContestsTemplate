using System;
using System.IO;
using HackerRankCSharp;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTestProject
{
    [TestClass]
    public class FilesTests
    {
        private String _basePath = "../../Resources/";

        [TestMethod]
        public void File0()
        {
            Test("Input0.txt", "Output0.txt");
        }

        [TestMethod]
        public void File1()
        {
            Test("Input1.txt", "Output1.txt");
        }

        [TestMethod]
        public void File2()
        {
            Test("Input2.txt", "Output2.txt");
        }

        [TestMethod]
        public void File3()
        {
            Test("Input3.txt", "Output3.txt");
        }

        [TestMethod]
        public void File4()
        {
            Test("Input4.txt", "Output4.txt");
        }

        [TestMethod]
        public void File5()
        {
            Test("Input5.txt", "Output5.txt");
        }

        private void Test(String expectedInputPath, String expectedOutputPath)
        {
            using (var streamReader = new StreamReader(_basePath + expectedInputPath))
            {
                Console.SetIn(streamReader);

                using (var memoryStream = new MemoryStream())
                {
                    using (var streamWriter = new StreamWriter(memoryStream))
                    {
                        Console.SetOut(streamWriter);

                        Program.Solve();
                        streamWriter.Flush();

                        memoryStream.Position = 0;
                        var actualOutputStream = new StreamReader(memoryStream);
                        Validate(new StreamReader(_basePath + expectedOutputPath), actualOutputStream);
                    }
                }
            }
        }

        private void Validate(StreamReader expectedOutputStream, StreamReader actualOutputStream)
        {
            while (!expectedOutputStream.EndOfStream)
            {
                Assert.AreEqual(expectedOutputStream.ReadLine(), actualOutputStream.ReadLine());
            }

            Assert.IsTrue(expectedOutputStream.EndOfStream == actualOutputStream.EndOfStream);
        }
    }
}
