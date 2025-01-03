"use client"

import { ReactNode, useEffect } from "react"
import { useAppDispatch, getOptionsFromLocal, getRandomChannel, getRandomUserId, useAppSelector } from "@/common"
import { setOptions, reset, fetchGraphDetails, setSelectedGraphId } from "@/store/reducers/global"
import { useGraphs } from "@/common/hooks";

interface AuthInitializerProps {
  children: ReactNode;
}

const AuthInitializer = (props: AuthInitializerProps) => {
  const { children } = props;
  const dispatch = useAppDispatch()
  const {initialize} = useGraphs()
  const selectedGraphId = useAppSelector((state) => state.global.selectedGraphId)
  const graphList = useAppSelector((state) => state.global.graphList)

  useEffect(() => {
    if (typeof window !== "undefined") {
      console.log("Starting initialization");
      const options = getOptionsFromLocal()
      initialize().catch(error => {
        console.error("Initialization failed:", error);
      });
      if (options && options.channel) {
        dispatch(reset())
        dispatch(setOptions(options))
      } else {
        dispatch(reset())
        dispatch(setOptions({
          channel: getRandomChannel(),
          userId: getRandomUserId(),
        }))
      }
    }
  }, [dispatch])

  useEffect(() => {
    if (graphList.length > 0 && !selectedGraphId) {
      // Select the first available graph as default
      dispatch(setSelectedGraphId(graphList[0]))
    }
  }, [graphList, selectedGraphId, dispatch])

  useEffect(() => {
    if (selectedGraphId) {
      dispatch(fetchGraphDetails(selectedGraphId));
    }
  }, [selectedGraphId, dispatch]); // Automatically fetch details when `selectedGraphId` changes

  return children
}


export default AuthInitializer;
