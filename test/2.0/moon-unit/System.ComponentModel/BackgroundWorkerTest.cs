//
// BackgroundWorker Unit Tests
//
// Contact:
//   Moonlight List (moonlight-list@lists.ximian.com)
//
// Copyright 2010 Novell, Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining
// a copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
// 
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
// OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

using System;
using System.ComponentModel;
using System.Threading;

using Microsoft.Silverlight.Testing;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace MoonTest.System.ComponentModel {

	[TestClass]
	public class BackgroundWorkerTest : SilverlightTest {

		[TestMethod]
		[Asynchronous]
		public void BackgroundWorker_ProgressChanged_WithoutStartingWork ()
		{
			bool complete = false;
			int tid = Thread.CurrentThread.ManagedThreadId;

			BackgroundWorker b = new BackgroundWorker ();
			b.WorkerReportsProgress = true;
			b.ProgressChanged += delegate (object sender, ProgressChangedEventArgs e) {
				// called on main thread
				Assert.AreEqual (tid, Thread.CurrentThread.ManagedThreadId, "ManagedThreadId");
				Assert.AreSame (b, sender, "sender");
				Assert.AreEqual (e.ProgressPercentage, 0, "ProgressPercentage");
				Assert.IsNull (e.UserState, "UserState");
				complete = true;
			};
			Assert.IsFalse (b.IsBusy, "#1");
			b.ReportProgress (0);
			EnqueueConditional (() => complete, TimeSpan.FromMilliseconds (20000));
			EnqueueTestComplete ();
		}
	}
}

