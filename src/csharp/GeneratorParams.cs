// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace Microsoft.ML.OnnxRuntimeGenAI
{
    public class GeneratorParams : IDisposable
    {
        private IntPtr _generatorParamsHandle;
        private bool _disposed = false;

        public GeneratorParams(Model model)
        {
            Result.VerifySuccess(NativeMethods.OgaCreateGeneratorParams(model.Handle, out _generatorParamsHandle));
        }

        internal IntPtr Handle { get { return _generatorParamsHandle; } }

        public void SetMaxLength(ulong maxLength)
        {
            Result.VerifySuccess(NativeMethods.OgaGeneratorParamsSetMaxLength(_generatorParamsHandle, (UIntPtr)maxLength));
        }

        public void SetInputIDs(ReadOnlySpan<int> inputIDs, ulong sequenceLength, ulong batchSize)
        {
            unsafe
            {
                fixed (int* inputIDsPtr = inputIDs)
                {
                    Result.VerifySuccess(NativeMethods.OgaGeneratorParamsSetInputIDs(_generatorParamsHandle, inputIDsPtr, (UIntPtr)inputIDs.Length, (UIntPtr)sequenceLength, (UIntPtr)batchSize));
                }
            }
        }

        public void SetInputSequences(Sequences sequences)
        {
            Result.VerifySuccess(NativeMethods.OgaGeneratorParamsSetInputSequences(_generatorParamsHandle, sequences.Handle));
        }

        ~GeneratorParams()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (_disposed)
            {
                return;
            }
            NativeMethods.OgaDestroyGeneratorParams(_generatorParamsHandle);
            _generatorParamsHandle = IntPtr.Zero;
            _disposed = true;
        }
    }
}